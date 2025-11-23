import os
import re
import shutil
from pathlib import Path
from invoke import Collection, task

import setup
from utils.logger import INFO, print_task_documentation
from utils.command_executor import CommandExecutor
from utils.windows.environment_utils import activate_VS2022_environment


@task(pre=[setup.setup_context])
def clang_format(ctx):
    """
    Format h/cpp files in LeetCode 
    """
    files = []

    def collect_file(dir):
        for item in os.listdir(f"{dir}"):
            item = Path(os.path.join(f"{dir}", item))
            if item.is_file():
                if item.name.endswith('.h') or item.name.endswith('.cpp'):
                    files.append(f'"{item.as_posix()}"')
            if item.is_dir():
                collect_file(f"{item}")

    collect_file(f'{ctx.leet_code_dir}/src')

    command = [
        "clang-format",
        f'^\n  -i',
        f'^\n  --verbose',
        f'^\n  --style="file:{ctx.git_dir}/.clang-format" ^\n ',
        " ^\n  ".join(files),
    ]

    CommandExecutor(ctx).execute(command, log="clang-format.log")


@task(pre=[setup.setup_context])
@print_task_documentation
def clean(ctx):
    """
    Clean Conan's data for LeetCode
    """
    for item in os.listdir(f"{ctx.leet_code_cmake_dir}"):
        item = Path(os.path.join(f"{ctx.leet_code_cmake_dir}", item))
        if item.is_dir():
            if item.name.startswith('.cache'):
                shutil.rmtree(item)
                INFO.log_line(f"remove CMake cache dir: {item}")
            elif item.name.startswith('.build'):
                shutil.rmtree(item)
                INFO.log_line(f"remove CMake build dir: {item}")


@task(
    pre=[setup.setup_context],
    help={
        "debug": "if set configuration type will be DEBUG (else RELEASE)",
    },
)
@print_task_documentation
def configure(ctx, debug=True):
    """
    Configure LeetCode-project
    """

    build_type = "Debug" if debug else "Release"

    command = [
        activate_VS2022_environment(),
        [
            f'cmake',
            f'^\n  -DCMAKE_CXX_COMPILER=clang-cl.exe',
            f'^\n  -DCMAKE_C_COMPILER=clang-cl.exe',
            f'^\n  -DCMAKE_BUILD_TYPE={build_type}',
            f'^\n  -GNinja',
            f'^\n  -DCMAKE_TOOLCHAIN_FILE="{ctx.leet_code_conan_dir}/.build_{build_type}/build/{build_type}/generators/conan_toolchain.cmake"',
            f'^\n  -S "{ctx.leet_code_dir}"',
            f'^\n  -B "{ctx.leet_code_cmake_dir}/.build_{build_type}"',
        ],
    ]

    CommandExecutor(ctx).execute(command, log="leet_code.configure.log")


@task(
    pre=[setup.setup_context],
    help={
        "debug": "if set build type will be DEBUG, else RELEASE (by default DEBUG)",
        "target": "defines name of target to build (by default ALL)",
        "jobs": "defines count parallel buildings (by default 8)",
    },
)
@print_task_documentation
def build(ctx, debug=True, target="all", jobs=8):
    """
    Build LeetCode-project
    """

    build_type = "Debug" if debug else "Release"

    command = [
        activate_VS2022_environment(),
        [
            f'ninja',
            f'^\n  -j {jobs}',
            f'^\n  {target}',
        ],
    ]

    CommandExecutor(ctx).execute(command, cwd=f"{ctx.leet_code_cmake_dir}/.build_{build_type}", log="leet_code.build.log")


@task(
    pre=[setup.setup_context],
    help={
        "debug": 'if set build type will be DEBUG, else RELEASE (by default DEBUG)',
        "target": 'defines regexpr-name of target to launch (by default ".+")',
        "gtest_filter": 'defines regexpr-filter for tests in targets (by default ".+")',
    },
)
@print_task_documentation
def launch(ctx, debug=True, target=".+", gtest_filter="*"):
    """
    Launch targets of LeetCode-project
    """

    build_type = "Debug" if debug else "Release"
    targets_dir = f"{ctx.leet_code_cmake_dir}/.build_{build_type}"

    command = []
    for item in os.listdir(f"{targets_dir}"):
        item = Path(os.path.join(f"{targets_dir}", item))
        if item.is_file():
            if item.name.endswith('.exe'):
                if re.match(target, item.name):
                    INFO.log_line(f'detected by "{target}": {item.name}')
                    command.append([
                        f'{item.name}',
                        f'--gtest_filter="{gtest_filter}"',
                    ])

    CommandExecutor(ctx).execute(command, cwd=f"{targets_dir}", log="leet_code.launch.log")


@task(
    pre=[setup.setup_context],
    help={
        "clean": "should clean all temporary files before checking",
        "debug": "if set build type will be DEBUG, else RELEASE (by default DEBUG)",
        "target": 'defines regexpr-name of target to launch (by default ".+")',
    },
)
@print_task_documentation
def full_check(ctx, clean=False, debug=True, target=".+"):
    """
    Full-check LeetCode-project
    """
    if clean:
        leet_code.conan.clean(ctx)
        leet_code.clean(ctx)

    leet_code.conan.install(ctx, debug=debug)
    leet_code.configure(ctx, debug=debug)
    leet_code.build(ctx, debug=debug)
    leet_code.launch(ctx, debug=debug, target=target)


collection = Collection("leet_code")
collection.add_task(clang_format, name="clang-format")
collection.add_task(clean, name="clean")
collection.add_task(configure, name="configure")
collection.add_task(build, name="build")
collection.add_task(launch, name="launch")
collection.add_task(full_check, name="full-check")

import leet_code.conan

collection.add_collection(leet_code.conan.collection)
