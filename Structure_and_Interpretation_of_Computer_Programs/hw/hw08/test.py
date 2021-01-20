class Link:

	empty = ()
	def __init__(self, first, rest=empty):
		assert rest is Link.empty or isinstance(rest, Link)
		self.first = first
		self.rest = rest

def display_nested(lnk):
	s = ''
	while lnk is not Link.empty:
		if isinstance(lnk.first, Link):
			s += ' ' + display_nested(lnk.first)
		else:
			s += ' ' + str(lnk.first)
		lnk = lnk.rest
	return '<' + s + ' >'

def display_nested_link(link):
	"""Display a string representation of the input linked list link, including the nested list"""
	str_num = ''
	while link is not Link.empty:
		if isinstance(link.first, Link):
			elem = display_nested_link(link.first)
		else:
			elem = str(link.first)
		str_num += elem + ' '
		link = link.rest
	return '< '+ str_num + '>'

l = Link(Link(1), Link(2, Link(3)))
print(display_nested(l))
print(display_nested_link(l))

class Foo:
	def __repr__(self):
		return 'print("exec foo")'

	def __str__(self):
		return 'str foo'

