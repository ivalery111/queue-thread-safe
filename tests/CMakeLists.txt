add_executable(test_queue_en_de test_queue_en_de.c)
target_link_libraries(test_queue_en_de utils::queue project_warnings sanitizers)
add_test(
    NAME test_queue_en_de
    COMMAND test_queue_en_de
)