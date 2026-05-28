import invoke
import platform


current_os = platform.system()
if current_os == "Windows":
    from . import windows as lc
elif current_os == "Linux":
    from . import linux as lc
else:
    raise RuntimeError("unexpected OS")


collection = invoke.Collection("leet-code")
collection.add_task(lc.clang_format, name="clang-format")
collection.add_task(lc.clean, name="clean")
collection.add_task(lc.configure, name="configure")
collection.add_task(lc.build, name="build")
collection.add_task(lc.launch, name="launch")
collection.add_task(lc.full_check, name="full-check")