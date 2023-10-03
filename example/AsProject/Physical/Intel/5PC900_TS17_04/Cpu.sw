<?xml version="1.0" encoding="utf-8"?>
<?AutomationStudio FileVersion="4.9"?>
<SwConfiguration CpuAddress="SL1" xmlns="http://br-automation.co.at/AS/SwConfiguration">
  <TaskClass Name="Cyclic#1">
    <Task Name="TestTask3" Source="TestTask2.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="TestTask4" Source="TestTask1.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="TestTask5" Source="TestTask2.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="TestTask6" Source="TestTask1.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="TestTask2" Source="TestTask2.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="TestTask1" Source="TestTask1.prg" Memory="UserROM" Language="IEC" Debugging="true" />
  </TaskClass>
  <TaskClass Name="Cyclic#2" />
  <TaskClass Name="Cyclic#3" />
  <TaskClass Name="Cyclic#4" />
  <TaskClass Name="Cyclic#5" />
  <TaskClass Name="Cyclic#6" />
  <TaskClass Name="Cyclic#7" />
  <TaskClass Name="Cyclic#8">
    <Task Name="webHMIProg" Source="webHMI.webHMIProg.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="systemInfo" Source="systemInfo.prg" Memory="UserROM" Language="IEC" Debugging="true" />
  </TaskClass>
  <Binaries>
    <BinaryObject Name="udbdef" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="TCData" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="FWRules" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="ashwd" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="ashwac" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="User" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="sysconf" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="asfw" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="arconfig" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="iomap" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Role" Source="" Memory="UserROM" Language="Binary" />
  </Binaries>
  <Libraries>
    <LibraryObject Name="omjson" Source="Libraries.Loupe.omjson.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="astime" Source="Libraries._AS.astime.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="runtime" Source="Libraries._AS.runtime.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="AsBrStr" Source="Libraries._AS.AsBrStr.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="AsBrWStr" Source="Libraries._AS.AsBrWStr.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="sys_lib" Source="Libraries._AS.sys_lib.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="AsHttp" Source="Libraries._AS.AsHttp.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="AsGuard" Source="Libraries._AS.AsGuard.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="AsTCP" Source="Libraries._AS.AsTCP.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="standard" Source="Libraries._AS.standard.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="vartools" Source="vartools.lby" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="stringext" Source="Libraries.Loupe.stringext.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="databuffer" Source="Libraries.Loupe.databuffer.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="tcpcomm" Source="Libraries.Loupe.tcpcomm.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="bodyguard" Source="Libraries.Loupe.bodyguard.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="asiodiag" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
  </Libraries>
</SwConfiguration>