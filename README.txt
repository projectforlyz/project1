Run the program with the txt called sample. Then you will get an input txt and get the final result you want. However, our code can only identy space instead of enter. So we should adjust each paragraph to get the output. Let's take the following word for example.
The actual Enumeration shall be made within three Years after the first Meeting of the Congress of the United States, and within every subsequent Term of ten Years, in such Manner as they shall by Law direct. The Number of Representatives shall not exceed one for every thirty Thousand, but each State shall have at Least one Representative; and until such enumeration shall be
made, the State of New Hampshire shall be entitled to choose three,Massahusetts eight, Rhode Island and Providence Plantations one, Connecticut five, New York six, New Jersey four, Pennsylvania eight, Delaware one, Maryland
six, Virginia ten, North Carolina five, South Carolina five and Georgia three.
Run the program with the sample.txt and see what you will get.
Here comes the our code:

#define N 1
#define MAX 10000
#include&lt;iostream&gt;
#include&lt;string&gt;
#include&lt;deque&gt;
#include&lt;vector&gt;
#include&lt;map&gt;
#include&lt;stdlib.h&gt;
#include&lt;ctime&gt;
#include&lt;sstream&gt;
#include&lt;fstream&gt;
using namespace std;
typedef deque&lt;string&gt; Prefix;
typedef vector&lt;string&gt; Postfix;
typedef map&lt;Prefix, Postfix&gt; mapping_table;

char fake_prefix[] = "\n";

void add_post(Prefix &pre, mapping_table &tab, const string &s)
{	
	if (pre.size() == N)
	{
		tab[pre].push_back(s);
		pre.pop_front();
	}
	pre.push_back(s);
}

void build_samp(Prefix &pre, mapping_table &tab, istream &in)
{
	string cur_word;
	while (in &gt;&gt; cur_word)
	{
		add_post(pre, tab, cur_word);
	}
}

void generate_sentence( mapping_table &tab)
{
	srand(time(NULL));
	Prefix prefix;
	for (int i = 0; i &lt; N; i++)
	{
		add_post(prefix,tab,fake_prefix);
	}
	for (int i = 0; i &lt; MAX; i++)
	{
		Postfix cur_post = tab[prefix];
		const string &w = cur_post[rand() % cur_post.size()];
		if (w == "\n") break;
		cout &lt;&lt; w&lt;&lt;" ";
		prefix.pop_front();
		prefix.push_back(w);
	}
	cout &lt;&lt; endl;
}

void main()
{
	Prefix pre_;
	mapping_table table_;
	for (int i = 0; i &lt; N; i++)
	{
		add_post(pre_, table_, fake_prefix);
	}
	//string sample_swntence = "my name is SongYang, my name is LiSiqi,my name is zuiniubi";
	string sample_sentence;
	ifstream fin("sample.txt");
	if (fin)
	{
		getline(fin, sample_sentence);
	}	
	else
	{
		cout &lt;&lt; "can't find the file"&lt;&lt;endl;
	}
	istringstream in(sample_sentence);
	build_samp(pre_, table_, in);
	add_post(pre_, table_, fake_prefix);
	generate_sentence(table_);
	system("pause");
}
We can tell from the result the backward word is choosen randomly after the forward word.
Basically, after the program scan all the text in the sample. It will remember which words have appeared after "the", just for example. Then while it's generating the text, it will choosen a word randomly from the words remebered in the forward step.
So we can get different results.
