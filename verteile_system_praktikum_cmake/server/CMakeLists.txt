project(Server)

include_directories(${PROJECT_SOURCE_DIR})

set(dependencies -lthrift -pthread -lpthread -lboost_system -lboost_thread)
set(genCpp gen-cpp/shop_constants.cpp gen-cpp/ShopRequest.cpp gen-cpp/shop_types.cpp)
set(serverSrcs source/Server.cpp source/MultiCastSender.cpp source/Sensor.cpp source/ShopConnection.cpp)

find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(Server ${serverSrcs} ${genCpp})

target_link_libraries(Server ${dependencies})
