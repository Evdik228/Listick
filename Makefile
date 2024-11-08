FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat                    \
-Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy     \
-Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op            \
-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow            \
-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn                           \
-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef              \
-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers                 \
-Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector             \
-fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla    \
-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr         

BUILD_FOLDER = objects/
SRC = src/
HED = include/
OBJECT_FILES = main.o utilities.o list_realize.o
COMPIL_P = $(addprefix $(BUILD_FOLDER), $(OBJECT_FILES))

Compile: $(COMPIL_P)
	g++  $(COMPIL_P) $(FLAGS) -o app 

$(BUILD_FOLDER)main.o : 
	g++ -c $(SRC)main.cpp -o $(BUILD_FOLDER)main.o

$(BUILD_FOLDER)utilities.o : $(SRC)utilities.cpp $(HED)utilities.h    
	g++ -c $(SRC)utilities.cpp -o $(BUILD_FOLDER)utilities.o 

$(BUILD_FOLDER)list_realize.o : $(SRC)list_realize.cpp $(HED)list_realize.h
	g++ -c $(SRC)list_realize.cpp -o $(BUILD_FOLDER)list_realize.o

clean:    

	rm ./objects/*.o app *.dot *.png  debug/dots/*.dot debug/img/*.png