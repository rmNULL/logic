#include "gates.h"
#include <assert.h>

typedef struct {
	Xor x;
	And a;
} halfadder;

/* 
 * Sum   = A x B 
 * Carry = A . B
 */
void set_defaults_halfadder(halfadder *h)
{
	h->x = create_Xor_gate("Sum", 2);
	h->a = create_And_gate("Carry", 2);

	short_pins(h->a, 0, h->x, 0, SHORT_IN);
	short_pins(h->a, 1, h->x, 1, SHORT_IN);
}


void half_adder(void)
{
	halfadder h;
	set_defaults_halfadder(&h);

	bool sum   = false;
	bool carry = false;

	int pinA, pinB;

	for (int i = 0; i < 4; i++) {
		pinA = i & 1;
		pinB = i >> 1;

		assert(set_pin(h.x, pinA) != -1);
		assert(set_pin(h.x, pinB) != -1);

		/* trying to set pins that are already set. */
		assert(set_pin(h.a, pinA) == -2);
		assert(set_pin(h.x, pinA) == -2);

		sum   = get_output(h.x);
		carry = get_output(h.a);

		assert(sum   == (pinA ^ pinB));
		assert(carry == (pinA & pinB));

		assert(unset_pin(h.x, 0) != -1);
		assert(unset_pin(h.x, 1) != -1);
	}

	cleanup(h.a);
	cleanup(h.x);

}

typedef struct {
	Xor xAB;
	Xor xS;

	And aAB;
	And aCxAB;

	Or oCout;
} fulladder;

/*
 * S    = (A x B) x Cin
 * Cout = (A . B) + ((A x B) . Cin )
 */
void set_defaults_fulladder(fulladder *f)
{

	f->xAB = create_Xor_gate("xAB", 2);
	f->xS = create_Xor_gate("xS", 2);

	f->aAB = create_And_gate("aAB", 2);
	f->aCxAB = create_And_gate("aCxAB", 2);

	f->oCout = create_Or_gate("oCout", 2);

	short_pins(f->xS, 0, f->xAB, 0, SHORT_OUT);

	short_pins(f->aAB, 0, f->xAB, 0, SHORT_IN);
	short_pins(f->aAB, 1, f->xAB, 1, SHORT_IN);

	short_pins(f->aCxAB, 0, f->xS, 0, SHORT_IN);
	short_pins(f->aCxAB, 1, f->xS, 1, SHORT_IN);

	short_pins(f->oCout, 0, f->aAB, 0, SHORT_OUT);
	short_pins(f->oCout, 1, f->aCxAB, 1, SHORT_OUT);
}


void full_adder(void)
{
	fulladder f;

	set_defaults_fulladder(&f);

	set_pin(f.xAB, 1);
	set_pin(f.xAB, 0);
	set_pin(f.xS, 1);

	bool sum = get_output(f.xS);
	bool carry = get_output(f.oCout);

	printf(" sum = %d\n", sum);
	printf(" Carry = %d\n", carry);

	cleanup(f.xAB);
	cleanup(f.xS);

	cleanup(f.aAB);
	cleanup(f.aCxAB);

	cleanup(f.oCout);
}
