MODULE_PATH = AI_modules
COMPILE_PATH = AI_modules/compilations

dynamicListInt.o: $(MODULE_PATH)/dynamicListInt.c
	gcc -c $(MODULE_PATH)/dynamicListInt.c -o $(COMPILE_PATH)/dynamicListInt.o

random.o: $(MODULE_PATH)/random.c
	gcc -c $(MODULE_PATH)/random.c -o $(COMPILE_PATH)/random.o

matrix.o: $(MODULE_PATH)/matrix.c
	gcc -c $(MODULE_PATH)/matrix.c -o $(COMPILE_PATH)/matrix.o

layer.o: $(MODULE_PATH)/layer.c
	gcc -c $(MODULE_PATH)/layer.c -o $(COMPILE_PATH)/layer.o

dynamicListMatrix.o: $(MODULE_PATH)/dynamicListMatrix.c
	gcc -c $(MODULE_PATH)/dynamicListMatrix.c -o $(COMPILE_PATH)/dynamicListMatrix.o

dynamicListLayer.o: $(MODULE_PATH)/dynamicListLayer.c
	gcc -c $(MODULE_PATH)/dynamicListLayer.c -o $(COMPILE_PATH)/dynamicListLayer.o

neuralNet.o: $(MODULE_PATH)/neuralNet.c
	gcc -c $(MODULE_PATH)/neuralNet.c -o $(COMPILE_PATH)/neuralNet.o

ai.o: $(MODULE_PATH)/ai.c
	gcc -c $(MODULE_PATH)/ai.c -o $(COMPILE_PATH)/ai.o

compile: dynamicListInt.o random.o matrix.o layer.o dynamicListMatrix.o dynamicListLayer.o neuralNet.o ai.o example.c
	gcc example.c $(COMPILE_PATH)/ai.o $(COMPILE_PATH)/neuralNet.o $(COMPILE_PATH)/dynamicListMatrix.o $(COMPILE_PATH)/dynamicListLayer.o $(COMPILE_PATH)/layer.o $(COMPILE_PATH)/matrix.o $(COMPILE_PATH)/random.o $(COMPILE_PATH)/dynamicListInt.o -lm -o example