CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = -pthread

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = obj
DATA_DIR = data

# Archivos fuente y objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out $(SRC_DIR)/main.cpp, $(SRCS)))

# Archivos de prueba y objetos
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

# Ejecutables
EXEC = $(BUILD_DIR)/main
TEST_GRAPH_EXEC = $(BUILD_DIR)/test_graph
TEST_MONTE_CARLO_EXEC = $(BUILD_DIR)/test_monte_carlo
TEST_THREAD_MANAGER_EXEC = $(BUILD_DIR)/test_thread_manager

all: $(EXEC)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(EXEC): $(OBJS) $(BUILD_DIR)/main.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(TEST_GRAPH_EXEC): $(OBJS) $(BUILD_DIR)/test_graph.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_MONTE_CARLO_EXEC): $(OBJS) $(BUILD_DIR)/test_monte_carlo_simulator.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_THREAD_MANAGER_EXEC): $(OBJS) $(BUILD_DIR)/test_thread_manager.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@rm -rf $(BUILD_DIR)/*.o $(EXEC) $(TEST_GRAPH_EXEC) $(TEST_MONTE_CARLO_EXEC) $(TEST_THREAD_MANAGER_EXEC)

test_graph: $(TEST_GRAPH_EXEC)
	$(TEST_GRAPH_EXEC)

test_monte_carlo: $(TEST_MONTE_CARLO_EXEC)
	$(TEST_MONTE_CARLO_EXEC)

test_thread_manager: $(TEST_THREAD_MANAGER_EXEC)
	$(TEST_THREAD_MANAGER_EXEC)

.PHONY: all clean test_graph test_monte_carlo test_thread_manager
