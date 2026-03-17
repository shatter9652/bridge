dependencies {
    // MCProtocolLib — Java Edition protocol (1.21.4)
    implementation("org.geysermc.mcprotocollib:protocol:1.21.11-SNAPSHOT")

    // Netty — LCE TCP frontend
    implementation("io.netty:netty-all:4.1.115.Final")

    // Gson — mapping JSON loading
    implementation("com.google.code.gson:gson:2.10.1")

    // Logging
    implementation("org.slf4j:slf4j-api:2.0.13")
    implementation("ch.qos.logback:logback-classic:1.5.6")

    // YAML config parsing
    implementation("org.yaml:snakeyaml:2.2")
}
