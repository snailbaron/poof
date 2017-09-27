CXX = clang++
CXXFLAGS += -std=c++17
LDLIBS += -lSDL2 -lSDL2_image -lSDL2_ttf

build_dir = ../../build
bin_dir = ../../bin

sources = $(shell find * -name '*.cpp')
objects = $(addprefix $(build_dir)/, $(sources:.cpp=.o))
deps = $(addprefix $(build_dir)/, $(sources:.cpp=.d))
client = $(addprefix $(bin_dir)/, poof)

all: $(client)

$(client): $(objects)
	mkdir -p ../../bin
	$(CXX) $(LDLIBS) -o $@ $(objects)

.PHONY: clean
clean:
	rm -rf $(build_dir) $(bin_dir)

$(build_dir)/%.d : %.cpp
	@set -e; \
	rm -f $@; \
	mkdir -p $(dir $@); \
	$(CXX) $(CXXFLAGS) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($(notdir $*)\).o[ :]*,$(patsubst %.d,%.o,$@) $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(build_dir)/%.o : %.cpp
	@echo 'o to cpp $@'
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

include $(deps)
