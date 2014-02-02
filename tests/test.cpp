#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

class RotationTest : public CppUnit::TestFixture {
public:
	void test() {
		CPPUNIT_ASSERT(1 == 1);
		CPPUNIT_ASSERT(1 == 0);
	}
};

int main() {
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestSuite suite;
	CppUnit::TestResult result;

	runner.addTest(new CppUnit::TestCaller<RotationTest>("testRotation", &RotationTest::test));
	
	bool res = runner.run();

	std::cout << "res: " << res << std::endl;

	if (res) {
		return 0;
	} else {
		return 1;
	}
}
