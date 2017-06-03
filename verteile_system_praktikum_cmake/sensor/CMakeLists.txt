project(Sensor)

include_directories(${PROJECT_SOURCE_DIR})

set(dependencies -pthread -lpthread -lboost_system -lboost_thread)
set(sensorSrcs source/Sensor_Client.cpp source/Sensor.cpp source/MultiCastReceiver.cpp)

find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(Sensor ${sensorSrcs})

target_link_libraries(Sensor ${dependencies})
