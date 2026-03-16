plugins {
    application
}

dependencies {
    implementation(project(":core"))
}

application {
    mainClass.set("dev.banditvault.lcebridge.standalone.BridgeMain")
}

tasks.jar {
    manifest {
        attributes["Main-Class"] = "dev.banditvault.lcebridge.standalone.BridgeMain"
    }
    // Fat jar — bundle all runtime deps
    from(configurations.runtimeClasspath.get().map { if (it.isDirectory) it else zipTree(it) })
    duplicatesStrategy = DuplicatesStrategy.EXCLUDE
}
