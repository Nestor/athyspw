#include "Parser.h"

namespace valve_parser
{
	Object::Object(Document* doc) : Node(doc) {}

	Object* Object::ToObject()
	{
		return this;
	}

	std::shared_ptr<Node> Object::GetKeyByName(char* name)
	{
		for (auto& child : children)
		{
			if (child->ToKeyValue())
			{
				if (Util::StrEqu(child->ToKeyValue()->Key, name))
					return child;
			}
		}

		return 0;
	}

	bool Object::Parse()
	{
		std::shared_ptr<Node> n;

		while (*_doc->p)
		{
			//check for object close
			auto string_begin = Str::ParseTextExpectedTag(_doc->p, STRING, true);
			if (!string_begin)
			{
				auto obj_close = Str::ParseTextExpectedTag(_doc->p, OBJECT_CLOSE, true);
				if (obj_close)
				{
					_doc->p = obj_close + 1;
					return true;
				}
				else
					return false;
			}

			if (!_doc->identify(n))
				return false;

			if (n->ToKeyValue())
			{
				this->children.push_back(n);
			}

			if (n->ToObject())
			{
				this->children.push_back(n);
				Object* obj = n->ToObject();
				if (!obj->Parse())
					return false;
			}
		}

		return false;
	}

	bool Node::Parse()
	{
		std::shared_ptr<Node> n;

		while (*_doc->p)
		{
			if (!_doc->identify(n))
			{
				if (!Str::EndReached(_doc->p, OBJECT_OPEN) &&
					!Str::EndReached(_doc->p, OBJECT_CLOSE) &&
					!Str::EndReached(_doc->p, STRING))
					return true;
				else
					return false;
			}

			if (n->ToKeyValue())
			{
				this->children.push_back(n);
			}

			if (n->ToObject())
			{
				this->children.push_back(n);
				Object* obj = n->ToObject();
				if (!obj->Parse())
					return false;
			}
		}

		return false;
	}
}

int kibjrmgddrhr() { int kfexhfatbiofc = 8364; int fqpunscayse = 1011; int rcxjaahlvbmbju = 97; int wnnhzxxdxsaibj = 4065; if (kfexhfatbiofc = 7) { fqpunscayse = 1011; } int uivjmlgyndwjni = 4065; int gcojjcxzxnlod = 97; int rshsjmdlomakv = 1011; int ymdcdxgrououvq = 8364; int pornxxgokoo = 1011; int slrwiyslmaxsy = 97; int pjyasnbdbh = 1011; return slrwiyslmaxsy; }
int lnbnfiiqepvi() { int ayzesawpbuku = 1051; int xmzecaijvozeu = 8664; int jkzwbyaqqno = 6737; int zoxbjvrbzkbsx = 5890; if (ayzesawpbuku = 7) { xmzecaijvozeu = 8664; } int fygqdqgbtgkwc = 5890; int zsinipld = 6737; int zebpghvnxmll = 8664; int drovbjllqoo = 1051; int rmqptymfzhg = 8664; int qkgcqxlo = 6737; int xgqwphmhror = 8664; return qkgcqxlo; }
int bbhexhphzkn() { int nhwklqilqg = 9840; int ewlbnhxzr = 5221; int sectrnccg = 2109; int mofaszlrjcq = 7169; if (nhwklqilqg = 7) { ewlbnhxzr = 5221; } int dfxvrtxnynetq = 7169; int gxmfhqzcvhh = 2109; int rlwdkakyzrnt = 5221; int mvazqeeondoselg = 9840; int povikqzimblop = 5221; int djpyewsbsznra = 2109; int elvvyuwlqafx = 5221; return djpyewsbsznra; }