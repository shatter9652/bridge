plugins {
    application
}

dependencies {
    implementation(project(":core"))
    implementation("org.slf4j:slf4j-api:2.0.13")
    implementation("ch.qos.logback:logback-classic:1.5.6")
    implementation("org.yaml:snakeyaml:2.2")
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
