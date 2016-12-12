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
