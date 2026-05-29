import os
import re
import shutil
import invoke
import pathlib
import commandscript

import conan_task

PROJECT_NAME = 'CppDetails'


def get_project_build_dir(debug=True, hold=True):
    build_type = "Debug" if debug else "Release"
    if hold:
        return f"{commandscript.ENV_CONTEXT.PROJECT_ARTIFACTS_DIR.name}/.build_{PROJECT_NAME}_{build_type}"
    else:
        return f"{commandscript.ENV_CONTEXT.PROJECT_ARTIFACTS_DIR.exp}/.build_{PROJECT_NAME}_{build_type}"


@commandscript.script_task(
    help={
        "conan": "if set configure conanfile.txt for LeetCode project too (by default: FALSE)",
        "debug": "if set configuration type will be DEBUG, else RELEASE (by default: TRUE)",
    })
def configure(ctx, conan=False, debug=True):
    """
    Configure LeetCode-project
    """
    build_type = "Debug" if debug else "Release"

    if conan:
        assert not conan_task.install(
            ctx,
            script_dir=ctx.script_dir,
            launch=ctx.launch,
            conanfile_dir=commandscript.ENV_CONTEXT.LEET_CODE_DIR.exp,
            profile_path=f'{commandscript.ENV_CONTEXT.CONAN_PROFILES_DIR.name}/profile_linux.txt',
            project_name=PROJECT_NAME,
            debug=build_type)

    commandscript.ScriptExecutor.from_ctx(ctx)\
        .add_command([
                f'cmake',
                f'-DCMAKE_BUILD_TYPE={build_type}',
                f'-DCMAKE_TOOLCHAIN_FILE="{conan_task.get_toolchain_file_path(build_type, PROJECT_NAME)}"',
                f'-GNinja',
                f'-S "{commandscript.ENV_CONTEXT.CPP_DETAILS_DIR.name}"',
                f'-B "{get_project_build_dir(build_type)}"',
            ])\
        .execute(log="cpp-details.configure.log")


@commandscript.script_task(
    help={
        "debug": "if set build type will be DEBUG, else RELEASE (by default: TRUE)",
        "target": "defines name of target to build (by default: ALL)",
        "jobs": "defines count parallel buildings (by default: 8)",
    }, )
def build(ctx, debug=True, target="all", jobs=8):
    """
    Build CppDetails-project
    """
    commandscript.ScriptExecutor.from_ctx(ctx)\
        .add_cwd(get_project_build_dir(debug))\
        .add_command([f'ninja -j {jobs} {target}'])\
        .add_command([f"ninja -t compdb > compile_commands.json"])\
        .execute(log="cpp-details.build.log")
