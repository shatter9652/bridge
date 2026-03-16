rootProject.name = "LCEBridge"

include("core")
include("bootstrap-standalone")

// Redirect all subproject build dirs into _build/ so the root stays clean
gradle.allprojects {
    layout.buildDirectory.set(File(rootDir, "_build/${project.name}"))
}
