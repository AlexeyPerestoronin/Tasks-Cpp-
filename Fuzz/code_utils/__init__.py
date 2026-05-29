import os
import pathlib
import invoke
import commandscript


@commandscript.script_task()
def yapf(ctx):
    """
    Format python files with Fuzz
    """
    commandscript.ScriptExecutor.from_ctx(ctx)\
        .add_cwd(commandscript.ENV_CONTEXT.PROJECT_FUZZ_DIR)\
        .add_command([
                'yapf',
                f'--style "{commandscript.ENV_CONTEXT.PROJECT_GIT_DIR}/.style.yapf"',
                '--verbose',
                '--recursive',
                '--in-place',
                '--parallel',
                f"--exclude '**.venv**'",
                f"{commandscript.ENV_CONTEXT.PROJECT_FUZZ_DIR}",
            ])\
        .execute(log="yapf.log")


@commandscript.script_task(help={
    "source-file-dir": "path to dir with C++ source files",
})
def clang_format(ctx, source_file_dir: str = None, log_file_name: str = None):
    """
    Format h/cpp files with clang-format 
    """
    assert source_file_dir
    assert log_file_name

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
                *collect_file(f'{source_file_dir}'),
        ])\
    .execute(log=log_file_name)


collection = invoke.Collection("code-utils")
collection.add_task(yapf, name="yapf")
collection.add_task(clang_format, name="clang-format")
