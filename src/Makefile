ROOTDIR = $(shell readlink -f '..')
NAME = Sweeper
SRCS = $(wildcard *.cpp) $(wildcard */*.cpp)
OBJS = ${SRCS:.cpp=.o}
CXXFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef -Werror -Wunused -Wdelete-non-virtual-dtor -Wno-long-long -Wno-unused-parameter -pipe -fno-exceptions
LDFLAGS = -lm -lsfml-graphics -lsfml-system -lsfml-window -Wl,-O1 -Wl,--no-undefined
INCFLAGS =
LNKFLAGS =

.PHONY: all clean debug release

all: debug

debug: CXXFLAGS += -g
debug: $(NAME)

release: CXXFLAGS += -O2
release: $(NAME)

%.o : %.cpp
		@$(CXX) -M -o $*.d $<
		@cp $*.d .$*.P;
		@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
			 -e '/^$$/ d' -e 's/$$/ :/' < $*.d >> .$*.P;
		@rm $*.d
		$(CXX) $(INCFLAGS) $(CXXFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LNKFLAGS) $(LDFLAGS)
	cp $(NAME) $(ROOTDIR)

clean:
	@ rm $(OBJS) 2>/dev/null || true
	@ rm $(NAME) 2>/dev/null || true
	@ rm $(ROOTDIR)/$(NAME) 2>/dev/null || true
	@ rm .*.P 2>/dev/null || true

-include $(SRCS:%.cpp=.%.P)
