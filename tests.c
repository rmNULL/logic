/* test cases */
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gates.h"

/* test prototypes */
void create_destroy_test(void);
void gate_class_tests(void);

void internal_Or_test(void);
void internal_Not_test(void);
void not_and_shorted(void);

/* to be written */
void internal_And_test(void);
void internal_Xor_test(void);
void internal_Xnor_test(void);
void internal_Nand_test(void);
void internal_Nor_test(void);


/*
 * prints all input pins that are set. Find a better way to do this. Maybe colllect
 * all the values in an array and send it back to the user for whatever he wants
 * to do(like print).
 */
void print_set_pins(struct gate *gate)
{
	/* int set_pins = gate->set_pins; */
	bool truth;

	char *tag = ginfo_tag(gate);
	printf(" %s :: %s\n", gate_names[ginfo_class(gate)], !(tag) ? "no gate name given" : tag);
	for (unsigned int i = 0; i < ginfo_capacity(gate); ++i) {
		truth = get_pin_value(gate, i);
		printf("Pin%d: %s\n", i, truth ? "true" : "false");
	}

	if (tag)
		free(tag);
	puts("");
}


int main(void)
{
	create_destroy_test();
	gate_class_tests();

	internal_Or_test();
	internal_Not_test();

	not_and_shorted();

}

void gate_class_tests(void)
{
	And and = create_And_gate("and", 4);
	assert(and);
	Or  or  = create_Or_gate("or", 4);
	assert(or);
	Not not = create_Not_gate("not");
	assert(not);
	Xor xor = create_Xor_gate("xor", 4);
	assert(xor);
	Xnor xn = create_Xnor_gate("xnor", 4);
	assert(xn);
	Nor nor = create_Nor_gate("nor", 4);
	assert(nor);
	Nand na = create_Nand_gate("na", 4);
	assert(na);

	assert(ginfo_class(na)  == NAND);
	assert(ginfo_class(nor) == NOR);
	assert(ginfo_class(xn)  == XNOR);
	assert(ginfo_class(xor) == XOR);
	assert(ginfo_class(not) == NOT);
	assert(ginfo_class(or)  == OR);
	assert(ginfo_class(and) == AND);

	cleanup(and);
	cleanup(or);
	cleanup(not);
	cleanup(xor);
	cleanup(xn);
	cleanup(nor);
	cleanup(na);
}

void internal_Or_test(void)
{
	Or or = create_Or_gate("or", 2);

	bool a, b;
	for (int i = 0; i < 4; ++i) {
		a = i & 1;
		b = i >> 1;
		set_pin(or, a);
		set_pin(or, b);

		assert(get_pin_value(or, 0) == a);
		assert(get_pin_value(or, 1) == b);

		assert(get_output(or) == (a | b));

		assert(unset_pin(or, 1) != -1);
		assert(unset_pin(or, 0) != -1);
	}

	cleanup(or);
}


void not_and_shorted(void)
{
	Not n1 = create_Not_gate("n1");
	assert(n1);

	set_pin(n1, 0);
	assert(get_pin_value(n1, 0) == 0);

	bool n1_op = get_output(n1);
	assert(n1_op == 1);

	And a1 = create_And_gate("a1", 2);
	assert(a1);

	short_pins(a1, 0, n1, 0, SHORT_OUT);
	assert(get_pin_value(a1, 0) == n1_op);

	set_pin(a1, 1);
	assert(get_pin_value(a1, 1) == 1);

	bool a1_op = get_output(a1);
	assert(a1_op == (n1_op & 1));

	cleanup(n1);
	cleanup(a1);
}


void internal_Not_test(void)
{
	Not n1 = create_Not_gate("n1");

	for (int i = 0; i < 2; i++) {
		set_pin(n1, i);
		assert(get_pin_value(n1, 0) == i);
		assert(ginfo_is_pin_set(n1, 0) == true);

		assert(get_output(n1) == !i);

		unset_pin(n1, 0);
		assert(ginfo_is_pin_set(n1, 0) == false);
	}

	cleanup(n1);
}


void create_destroy_test(void)
{
	And a1 = create_And_gate("a1", 0);
	assert(a1 == NULL);

	a1 = create_And_gate("a1", 2);
	assert(a1 != NULL);

	Or o1  = create_Or_gate("o1", 4);
	assert(o1 != NULL);

	Xor x1 = create_Xor_gate("x1", 8);
	assert(x1 != NULL);

	Xnor xn1 = create_Xnor_gate("xn", 8);
	assert(xn1 != NULL);

	Nand na1 = create_Nand_gate("na1", 16);
	assert(na1 != NULL);

	Nor n1 = create_Nor_gate("n1", 64);
	assert(n1 != NULL);

	Nor n2 = create_Nor_gate("n2", 65);
	assert(n2 == NULL);

	Not i1 = create_Not_gate("i1");
	assert(i1 != NULL);

	if (a1)  cleanup(a1);
	if (x1)  cleanup(x1);
	if (xn1) cleanup(xn1);
	if (o1)  cleanup(o1);
	if (na1) cleanup(na1);
	if (n1)  cleanup(n1);
	if (n2)  cleanup(n2);
	if (i1)  cleanup(i1);
}
