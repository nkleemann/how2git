#!/usr/bin/python

# Gibt fuer aussagenlogische Formeln Wertetabellen fuer .tex Dokumente aus
# Passt auf euren Input auf, ihr seid Informatiker

import sys

def is_operator(c):
	if c in ["&","|","^",">","=","~"]: return True
	return False

def get_precedence(o):
	if o in [">","="]: return 1
	if o in ["&","|","^"]: return 2
	if o in ["~"]: return 3
	return 0

def left_assoc(o):
	if o in ["&","|","^",">","="]: return True
	if o in ["~"]: return False

def convert_infix(infix):
	infix = infix.replace(" ", "")

	stack, queue = [], []
	postfix = ""

	for i in infix:
		if is_operator(i):
			while(len(stack) != 0
			and ((left_assoc(i)
			and (get_precedence(i) <= get_precedence(stack[-1]))
			or (not left_assoc(i) and (get_precedence(i) < get_precedence(stack[-1])))))):
				queue.append(stack.pop());
			stack.append(i)
		elif i == "(": stack.append(i)
		elif i == ")":
			while stack[-1] != "(":
				queue.append(stack.pop())
			stack.pop()
		else:
			queue.append(i)

	while len(stack) != 0:
		queue.append(stack.pop())

	return(queue)

def get_operands(postfix):
	operands = []
	for i in postfix:
		if not is_operator(i): operands.append(i)

	seen = set()
	seen_add = seen.add
	operands = [ x for x in operands if not (x in seen or seen_add(x))]
	return operands

def parse_postfix(postfix, values):
	stack = []
	for i in postfix:
		if not is_operator(i):
			stack.append(int(values[i]))
		else:
			if i == "&":
				stack.append(stack.pop() & stack.pop())
			elif i == "|":
				stack.append(stack.pop() | stack.pop())
			elif i == "^":
				stack.append(stack.pop() ^ stack.pop())
			elif i == "~":
				stack.append(~stack.pop()+2)
			elif i == ">":
				b = stack.pop()
				a = stack.pop()
				stack.append((~a+2) | b)
			elif i == "=":
				b = stack.pop()
				a = stack.pop()
				stack.append(int(a == b))
	if len(stack) > 1:
		sys.stdout.write("Ungueltige Aussage\n")
		exit()

	return stack.pop()

def get_tests(operands):
	num = len(operands)
	vectors = []
	for x in range(pow(2,num)):
		v = list(('{0:0'+str(num)+'b}').format(x))
		vectors.append(dict(zip(operands, v)))
	return vectors

def print_table(exp, sep=" ", endl="\n"):
	if isinstance(exp, str): exp = [exp]

	postfix = []
	operands = []
	for e in exp:
		postfix.append(convert_infix(e))

		ops = get_operands(postfix[-1])
		for op in ops:
			if op not in operands:
				operands.append(op)

	tests = get_tests(operands)

	sys.stdout.write(sep.join(operands)+sep+sep.join(exp)+endl)

	for t in tests:
		sys.stdout.write((sep.join([t[x] for x in operands])))
		for e in postfix:
			sys.stdout.write(sep+str(parse_postfix(e, t)))
		sys.stdout.write(endl)

print("Symbolverzeichnis:")
print("""
~A  - "NICHT A"
A &  - "A UND B"
A | B - "A ODER B"
A ^ B - "ENTWEDER A ODER B"
A > B - "A IMPLIZIERT B"
A = B - "A AEQUIVALENT B"
Grundlegende Vorrangregeln sind implementiert, setze Klammern aber besser selbst.
Multiple Formeln mit Kommata trennen.
""")

if sys.version_info[0] < 3: i = raw_input("Formel: ").split(",")
else: i = input("Formel:  ").split(",")

sys.stdout.write("\n")

# Default formatting
#print_table(i)

# A bit prettier...
#print_table(i, "\t")

# LaTeX formatted output
print_table(i, " & ", " \\\\\n")

if sys.version_info[0] < 3: i = raw_input("\n[Enter] zum Beenden...")
else: i = input("\n[Enter] zum Beenden...")
