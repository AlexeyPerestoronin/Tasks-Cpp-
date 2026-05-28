import os
import re
import shutil
import invoke
import commandscript

import conan_task

PROJECT_NAME = 'LeetCode'


@commandscript.script_task()
def clean(ctx):
    """
    Clean Conan's data for LeetCode
    """
    pass


@commandscript.script_task(
    help={
        "conan": "if set configure conanfile.txt for LeetCode project too (by default: FALSE)",
        "debug": "if set configuration type will be DEBUG, else RELEASE (by default: TRUE)",
    }, )
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
            conanprofile_name='conanprofile_linux.txt',
            project_name=PROJECT_NAME,
            debug=build_type)

    commandscript.ScriptExecutor.from_ctx(ctx)\
        .add_command([
                f'cmake',
                f'-DCMAKE_BUILD_TYPE={build_type}',
                f'-DCMAKE_TOOLCHAIN_FILE="{conan_task.get_toolchain_file_path(build_type, PROJECT_NAME)}"',
                f'-GNinja',
                f'-S "{commandscript.ENV_CONTEXT.LEET_CODE_DIR}"',
                f'-B f"{commandscript.ENV_CONTEXT.PROJECT_ARTIFACTS_DIR.name}/.build_{PROJECT_NAME}_{build_type}"',
            ])\
        .execute(log="leet-code.configure.log")


@commandscript.script_task(
    help={
        "debug": "if set build type will be DEBUG, else RELEASE (by default DEBUG)",
        "target": "defines name of target to build (by default ALL)",
        "jobs": "defines count parallel buildings (by default 8)",
    }, )
def build(ctx, debug=True, target="all", jobs=8):
    """
    Build LeetCode-project
    """
    pass


@commandscript.script_task(
    help={
        "debug": 'if set build type will be DEBUG, else RELEASE (by default DEBUG)',
        "target": 'defines regexpr-name of target to launch (by default ".+")',
        "gtest_filter": 'defines regexpr-filter for tests in targets (by default ".+")',
    }, )
def launch(ctx, debug=True, target=".+", gtest_filter="*"):
    """
    Launch targets of LeetCode-project
    """
    pass


@commandscript.script_task(
    help={
        "clean": "should clean all temporary files before checking",
        "debug": "if set build type will be DEBUG, else RELEASE (by default DEBUG)",
        "detect_conan_profile": "detect Conan's profile for the fist time (by default False)",
        "target": 'defines regexpr-name of target to launch (by default ".+")',
    }, )
def full_check(ctx, clean=False, debug=True, detect_conan_profile=False, target=".+"):
    """
    Full-check LeetCode-project
    """
    pass
