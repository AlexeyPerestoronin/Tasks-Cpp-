import os
import pathlib
import invoke
import platform
import commandscript

current_os = platform.system()
if current_os == "Windows":
    from . import windows as lc
elif current_os == "Linux":
    from . import linux as lc
else:
    raise RuntimeError("unexpected OS")


@commandscript.script_task()
def clang_format(ctx):
    """
    Format h/cpp files in LeetCode 
    """

    def collect_file(dir):
        files = []
        for item in os.listdir(f"{dir}"):
            item = pathlib.Path(os.path.join(f"{dir}", item))
            if item.is_file():
                if item.name.endswith('.h') or item.name.endswith('.cpp'):
                    files.append(f'"{item.as_posix()}"')
            if item.is_dir():
                files.extend(collect_file(f"{item}"))
        return files

    commandscript.ScriptExecutor.from_ctx(ctx)\
        .add_cwd(commandscript.ENV_CONTEXT.PROJECT_GIT_DIR)\
        .add_command([
                "clang-format",
                f'-i',
                f'--verbose',
                f'--style="file:{commandscript.ENV_CONTEXT.PROJECT_GIT_DIR}/.clang-format"',
                *collect_file(f'{commandscript.ENV_CONTEXT.LEET_CODE_DIR.exp}/src'),
        ])\
    .execute(log="leet-code.clang-format.log")


collection = invoke.Collection("leet-code")
collection.add_task(clang_format, name="clang-format")
collection.add_task(lc.clean, name="clean")
collection.add_task(lc.configure, name="configure")
collection.add_task(lc.build, name="build")
collection.add_task(lc.launch, name="launch")
collection.add_task(lc.full_check, name="full-check")
