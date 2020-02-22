cmake_minimum_required(VERSION 3.15)
project(flightsimulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)


add_executable(flightsimulator main.cpp Command.h Parser.h OpenDataServer.cpp OpenDataServer.h CreateVarCommand.h
        SleepCommand.cpp SleepCommand.h CreateVarCommand.cpp  Var.cpp SetCommand.cpp SetCommand.h Interpreter.cpp Interpreter.h Expression.h
        ex1.cpp ex1.h Parser.cpp SymbolTable.h SymbolTable.cpp printCommand.cpp printCommand.cpp whileCommand.cpp whileCommand.h lexer.cpp lexer.h ifCommand.h ifCommand.cpp DataReaderServer.cpp DataReaderServer.h
        ConnectClientCommand.h ConnectClientCommand.cpp createFunctionCommand.cpp createFunctionCommand.h runFunctionCommand.cpp runFunctionCommand.h)

