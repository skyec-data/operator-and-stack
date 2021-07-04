stack<char> opt;     //Operator stack
stack<double> val;   //The operand stack

char opt_set[10] = "+-*/()=.";

bool in_set(char theChar) {
	for (int i = 0; i < 8; i++) {
		if (theChar == opt_set[i])
			return true;
	}
	return false;
}

int level(char theOpt)
{
	switch (theOpt) {
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case ')':
		return 3;
	}
}

bool del_space(string& theString)
{
	string res;
	for (int i = 0; i < theString.length(); i++) {
		if (in_set(theString[i]) || isdigit(theString[i]))
			res += theString[i];
		else if (theString[i] == ' ') {}
		else {
			cout << "The enter is Wrong" << endl;
			return false;
		}
	}
	theString = res;
	return true;
}

const int IN = 0;    // in the numbers
const int OUT = 1;    // outside the numbers

bool change(string& from, string& to)
{
	int theInt = 0;
	int state = OUT;
	char c;

	for (int i = 0; i < from.length(); i++)
	{
		c = from[i];
		if (isdigit(c)) {
			to = to + c;
			theInt *= 10;
			theInt += c - '0';
			state = IN; //The status is changed to within the number
		}
		else {
			if (state == IN && c == '.') {
				to = to + '.';
				theInt = 0;
				continue;
			}
			if (state == IN && c != '.') {
				to += ' ';
				theInt = 0;
			}
			if (c == '=')
				break;
			else if (c == '(')
				opt.push(c);
			else if (c == ')') {
				while (!opt.empty() && opt.top() != '(') {
					to += opt.top();
					to += ' ';
					opt.pop();
				}
				opt.pop();
			}
			else {
				while (true) {
					if (opt.empty() || opt.top() == '(')
						opt.push(c);
					else if (level(c) > level(opt.top()))
						opt.push(c);
					else {
						to += opt.top();
						to += ' ';
						opt.pop();
						continue;
					}
					break;
				}
			}
			state = OUT; //The status is outside the number
		}
	}
	while (!opt.empty()) {
		to += opt.top();
		to += ' ';
		opt.pop();
	}
	return true;
}

bool compute(string& theExp)
{
	int theInt = 0; //Temporary number
	int state = OUT;//The initial state is outside the number
	char c;
	bool dot = false;
	double count = 1.0;
	for (int i = 0; i < theExp.length(); i++)
	{
		c = theExp[i];
		if (isdigit(c) || c == '.') {
			if (isdigit(c)) {
				theInt *= 10;
				theInt += c - '0';
				state = IN; //The status is within the number
				if (dot == true)
					count *= 10.0;
			}
			if (c == '.') {
				dot = true;
				continue;
			}
		}
		else {
			dot = false;
			double ans = theInt / count;
			count = 1.0;
			if (state == IN) {
				val.push(ans);
				theInt = 0;
			}
			double x, y;
			if (c != ' ') {
				x = val.top(); val.pop();
				y = val.top(); val.pop();

				switch (c) {
				case '+':val.push(x + y); break;
				case '-':val.push(y - x); break;
				case '*':val.push(x * y); break;
				case '/':val.push(y / x); break;
				default:cout << "Unknown error!" << endl;
				}
			}
			state = OUT;
		}
	}
	return true;
}
