CC = gcc

CFLAGS=
CSRCFLAGS=
LFLAGS=

# Location of the files
CLI_SRC       = ./src/client
ADM_SRC       = ./src/admin
HEAD          = ./include
COMMON_SRC    = ./src/common

OBJ_DIR       = ./objects

CLISOURCES    = $(wildcard $(CLI_SRC)/*.c)
ADMSOURCES    = $(wildcard $(ADM_SRC)/*.c)
COMMONSOURCES = $(wildcard $(COMMON_SRC)/*.c)
HEADERS       = $(wildcard $(HEAD)/*.h)

CLI_OBJECTS   = $(patsubst $(COMMON_SRC)/%.c, $(OBJ_DIR)/%.o, $(COMMONSOURCES))
CLI_OBJECTS  += $(patsubst $(CLI_SRC)/%.c, $(OBJ_DIR)/%.o, $(CLISOURCES))

ADM_OBJECTS   = $(patsubst $(COMMON_SRC)/%.c, $(OBJ_DIR)/%.o, $(COMMONSOURCES))
ADM_OBJECTS  += $(patsubst $(ADM_SRC)/%.c, $(OBJ_DIR)/%.o, $(ADMSOURCES))

CLI_OUT=dist/client
ADM_OUT=dist/admin

build:
	make build_cli
	make build_adm

build_cli: $(CLI_OBJECTS) $(HEADERS)
	mkdir -p dist
	echo $(CLI_OBJECTS)
	$(CC) -o $(CLI_OUT) $(LFLAGS) $(CLI_OBJECTS)

build_adm: $(ADM_OBJECTS) $(HEADERS)
	mkdir -p dist
	echo $(ADM_OBJECTS)
	$(CC) -o $(ADM_OUT) $(LFLAGS) $(ADM_OBJECTS)

$(OBJ_DIR)/%.o: $(CLI_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(CLI_SRC) -I$(HEAD) -c $< -o $@ $(CSRCFLAGS)

$(OBJ_DIR)/%.o: $(COMMON_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(CLI_SRC) -I$(HEAD) -c $< -o $@ $(CSRCFLAGS)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf dist/
