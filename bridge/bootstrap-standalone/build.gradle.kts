plugins {
    application
    id("com.github.johnrengelman.shadow") version "8.1.1"
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

tasks.shadowJar {
    manifest {
        attributes["Main-Class"] = "dev.banditvault.lcebridge.standalone.BridgeMain"
    }
    archiveClassifier.set("")
    mergeServiceFiles()
}
