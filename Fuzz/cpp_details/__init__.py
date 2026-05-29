import invoke
import platform
import commandscript

import code_utils

current_os = platform.system()
if current_os == "Windows":
    from . import windows as cppd
elif current_os == "Linux":
    from . import linux as cppd
else:
    raise RuntimeError("unexpected OS")


@commandscript.script_task()
def clang_format(ctx):
    """
    Format h/cpp files in LeetCode 
    """
    assert code_utils.clang_format(
        ctx, script_dir=ctx.script_dir, launch=ctx.launch, source_file_dir=f'{commandscript.ENV_CONTEXT.LEET_CODE_DIR.exp}/tasks', log_file_name="cpp-details.clang-format.log")


collection = invoke.Collection("leet-code")
collection.add_task(clang_format, name="clang-format")
collection.add_task(cppd.configure, name="configure")
collection.add_task(cppd.build, name="build")