target_sources(${PROJECT_NAME}_lib
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Router.cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Router.hpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Method.hpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Request.cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Request.hpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Response.cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Response.hpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Types.hpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/AbstractMessage.cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/AbstractMessage.hpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/RouterPipeline.cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/RouterPipeline.hpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/RouterPipelineStep.cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/RouterPipelineStep.hpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/RouterPipelineBuilder.cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/RouterPipelineBuilder.hpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Middleware.cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Middleware.hpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/RouteHandler.cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/RouteHandler.hpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PathMatcher.cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/PathMatcher.hpp
)
