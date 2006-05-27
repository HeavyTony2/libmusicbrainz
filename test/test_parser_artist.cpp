#include <fstream>
#include <string>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include <musicbrainz3/mbxmlparser.h>
#include <musicbrainz3/metadata.h>
#include <musicbrainz3/model.h>

using namespace std;
using namespace MusicBrainz;

#include "read_file.h"

class ParseArtistTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ParseArtistTest);
	CPPUNIT_TEST(testArtistBasic);
	CPPUNIT_TEST(testArtistAliases);
	CPPUNIT_TEST(testArtistReleases);
	CPPUNIT_TEST_SUITE_END();
	
protected:

	void testArtistBasic()
	{
		Metadata *md = MbXmlParser().parse(get_file_contents("../test-data/valid/artist/Tori_Amos_1.xml"));
		Artist *artist = md->getArtist();
		
		CPPUNIT_ASSERT(artist);
		CPPUNIT_ASSERT_EQUAL(string("http://musicbrainz.org/artist/c0b2500e-0cef-4130-869d-732b23ed9df5"), artist->getId());
		CPPUNIT_ASSERT_EQUAL(string("Tori Amos"), artist->getName());
		CPPUNIT_ASSERT_EQUAL(string("Amos, Tori"), artist->getSortName());
		CPPUNIT_ASSERT_EQUAL(string("1963-08-22"), artist->getBeginDate());
		CPPUNIT_ASSERT_EQUAL(0, int(artist->getReleases().size()));
	}
	
	void testArtistAliases()
	{
		Metadata *md = MbXmlParser().parse(get_file_contents("../test-data/valid/artist/Tori_Amos_4.xml"));
		const ArtistAliasList &al = md->getArtist()->getAliases();
		
		CPPUNIT_ASSERT_EQUAL(3, int(al.size()));
		CPPUNIT_ASSERT_EQUAL(string("Myra Ellen Amos"), al[0]->getValue());
		CPPUNIT_ASSERT_EQUAL(string("Latn"), al[2]->getScript());
		CPPUNIT_ASSERT_EQUAL(string(NS_MMD_1 + "Misspelling"), al[2]->getType());
	}
	
	void testArtistReleases()
	{
		Metadata *md = MbXmlParser().parse(get_file_contents("../test-data/valid/artist/Tori_Amos_2.xml"));
		const ReleaseList &re = md->getArtist()->getReleases();
		
		CPPUNIT_ASSERT_EQUAL(3, int(re.size()));
		CPPUNIT_ASSERT_EQUAL(string("To Venus and Back (disc 1: Orbiting)"), re[1]->getTitle());
		CPPUNIT_ASSERT_EQUAL(3, int(re[1]->getReleaseEvents().size()));
		CPPUNIT_ASSERT_EQUAL(string("DE"), re[2]->getReleaseEvents()[0]->getCountry());
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION(ParseArtistTest); 

