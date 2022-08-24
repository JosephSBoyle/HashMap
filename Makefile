CC=gcc
CFLAGS=-O3

src_dir := src
build_dir := build
target := run

code := $(wildcard $(src_dir)/*.c)
objects := $(patsubst $(src_dir)/%.c, $(build_dir)/%.o, $(code))

$(target): $(objects)
	$(CC) $(CFLAGS) $^ -o $@

$(build_dir)/%.o: $(src_dir)/%.c $(build_dir)
	$(CC) $(CFLAGS) -c $< -o $@

$(build_dir):
	mkdir -p $(build_dir)

clean:
	rm -r $(build_dir)
	rm $(target)
