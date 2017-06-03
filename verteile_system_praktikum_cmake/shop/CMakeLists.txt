project(Shop)

include_directories(${PROJECT_SOURCE_DIR})

set(dependencies -lthrift -lthriftnb -levent -pthread -lpthread -lboost_system -lboost_thread)
set(genCpp gen-cpp/shop_constants.cpp gen-cpp/ShopRequest.cpp gen-cpp/shop_types.cpp)
set(shopSrcs source/shop.cpp)

find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(Shop ${shopSrcs} ${genCpp})

target_link_libraries(Shop ${dependencies})
