PROGRAM = palindrome

ASFLAGS = -g -c

LDFLAGS = -g


SRCS     = $(wildcard *.s)

OBJS = $(subst .s,.o,$(SRCS))

LISTINGS = $(subst .s,.lst,$(SRCS))


default: $(PROGRAM) $(LISTINGS)

# Note that we use "-EB" to force big-endianness in listings, even
# though the ci20 and the textbook are little-endian. This is so that
# students can figure out ASCII string encodings working from
# left-to-right in the hex code.
%.lst: %.s
	$(AS) -EB -a=$@ -o /dev/null $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(LISTINGS) *~ a.out core

.PHONY: immaculate
immaculate: clean
	rm -f $(PROGRAM)

.PHONY: untabify
untabify:
	for file in $(SRCS) ;\
	do \
		expand -4 $$file >temp$$$$.s && mv temp$$$$.s $$file ;\
	done

# Note that we use $(CC) to do the assembly. We could use $(AS), but
# this would require setting a bunch of confusing flags.
%.o: %.s
	$(CC) $(ASFLAGS) -o $@ $^

# Here's the load command.
$(PROGRAM): palindrome.o #palindrome_functions.o
	$(CC) $(LDFLAGS) -o a.out $^
