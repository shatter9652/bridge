@rem Gradle wrapper for Windows
@if "%DEBUG%"=="" @echo off
@rem ##########################################################################
@rem  Gradle startup script for Windows
@rem ##########################################################################
set DIRNAME=%~dp0
if "%DIRNAME%"=="" set DIRNAME=.
set APP_BASE_NAME=%~n0

set GRADLE_OPTS=-Dfile.encoding=UTF-8

set DEFAULT_JVM_OPTS="-Xmx64m" "-Xms64m"

set CLASSPATH=%DIRNAME%gradle\wrapper\gradle-wrapper.jar

java %DEFAULT_JVM_OPTS% %JAVA_OPTS% ^
  -classpath "%CLASSPATH%" ^
  org.gradle.wrapper.GradleWrapperMain %*
