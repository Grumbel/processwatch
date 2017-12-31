env = Environment(
    CXX        = "i686-w64-mingw32-g++",
    AR         = "i686-mingw32msvc-ar",
    RANLIB     = "i686-mingw32msvc-ranlib",
    LINKFLAGS    = ["-static-libgcc"],
    LIBS       = ["psapi"],
    CPPDEFINES = [("PSAPI_VERSION", "1")],
    PROGSUFFIX = '.exe'
)
env.Program('processwatch', ["processwatch.cpp"])

# EOF #
