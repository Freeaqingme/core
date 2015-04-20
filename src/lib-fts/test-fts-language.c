/* Copyright (c) 2014-2015 Dovecot authors, see the included COPYING file */

#include "lib.h"
#include "test-common.h"
#include "fts-language.h"
/* TODO: These checks will not work without proper libtextcat configuration. 
   As such, they are not really unit test to be coupled with the build. */

const char *const settings[] =
	{"fts_language_config", TEST_TEXTCAT_DIR"/fpdb.conf",
	 "fts_language_data", TEST_TEXTCAT_DIR"/LM/", NULL};

/* Detect Finnish. fi--utf8 */
static void test_fts_language_detect_finnish(void)
{
	struct fts_language_list *lp = NULL;
	const struct fts_language *lang_r = NULL;
	const unsigned char finnish[] =
		"Yhdistyneiden kansakuntien kolmas yleiskokous hyv\xC3\xA4ksyi "\
		"ja julkisti ihmisoikeuksien yleismaailmallisen julistuksen "\
		"joulukuun 10. p\xC3\xA4iv\xC3\xA4n\xC3\xA4 1948. Julistuksen "\
		"hyv\xC3\xA4ksymisen puolesta \xC3\xA4\xC3\xA4nesti 48 maata. "\
		"Mik\xC3\xA4\xC3\xA4n maa ei \xC3\xA4\xC3\xA4nest\xC3\xA4nyt "\
		"vastaan. Kahdeksan maata pid\xC3\xA4ttyi "\
		"\xC3\xA4\xC3\xA4nest\xC3\xA4m\xC3\xA4st\xC3\xA4.";
	const char names[] = "de, fi, en";
	const char *unknown;
	test_begin("fts language detect Finnish");
	lp = fts_language_list_init(settings);
	test_assert(lp != NULL);
	test_assert(fts_language_list_add_names(lp, names, &unknown) == TRUE);
	test_assert(fts_language_detect(lp, finnish, sizeof(finnish)-1, &lang_r)
	            == FTS_LANGUAGE_RESULT_OK);
	test_assert(strcmp(lang_r->name, "fi") == 0);
	fts_language_list_deinit(&lp);
	test_end();
}

/* Detect English */
static void test_fts_language_detect_english(void)
{
	struct fts_language_list *lp = NULL;
	const struct fts_language *lang_r = NULL;
	const unsigned char english[]  = "Whereas recognition of the inherent dignity and"\
		" of the equal and inalienable rights of all members of the human"\
		"family is the foundation of freedom, justice and peace in the "\
		"world,\n Whereas disregard and contempt for human rights have "\
		"resulted in barbarous acts which have outraged the conscience"\
		"of mankind, and the advent of a world in which human beings"\
		"shall enjoy freedom of speech and belief and freedom from "\
		"fear and want has been proclaimed as the highest aspiration"\
		"of the common people, ";

	const char names[] = "fi, de, fr, en";
	const char *unknown;
	test_begin("fts language detect English");
	lp = fts_language_list_init(settings);
	test_assert(lp != NULL);
	test_assert(fts_language_list_add_names(lp, names, &unknown) == TRUE);
	test_assert(fts_language_detect(lp, english, sizeof(english)-1, &lang_r)
	            == FTS_LANGUAGE_RESULT_OK);
	test_assert(strcmp(lang_r->name, "en") == 0);
	fts_language_list_deinit(&lp);
	test_end();
}

/* Detect French */
static void test_fts_language_detect_french(void)
{
	struct fts_language_list *lp = NULL;
	const struct fts_language *lang_r = NULL;
	const unsigned char french[] =
		"D\xC3\xA9""claration universelle des droits de l\xE2\x80\x99"
		"homme Pr\xC3\xA9""ambule Consid\xC3\xA9rant que la "\
		"reconnaissance de la dignit\xC3\xA9 inh\xC3\xA9rente \xC3\xA0"\
		" tous les membres de la famille humaine et de leurs droits "\
		"\xC3\xA9gaux et inali\xC3\xA9nables constitue le fondement de"\
		" la libert\xC3\xA9, de la justice et de la paix dans le monde,"\
		" Consid\xC3\xA9rant que la m\xC3\xA9""connaissance et le "\
		"m\xC3\xA9pris des droits de l\xE2\x80\x99homme ont conduit "\
		"\xC3\xA0 des actes de barbarie qui r\xC3\xA9voltent la "\
		"conscience de l\xE2\x80\x99humanit\xC3\xA9 et que "\
		"l\xE2\x80\x99""av\xC3\xA8nement d\xE2\x80\x99un monde o\xC3\xB9"\
		" les \xC3\xAAtres humains seront libres de parler et de "\
		"croire, lib\xC3\xA9r\xC3\xA9s de la terreur et de la "\
		"mis\xC3\xA8re, a \xC3\xA9t\xC3\xA9 proclam\xC3\xA9 comme la "\
		"plus haute aspiration de l\xE2\x80\x99homme,";


	const char names[] = "de, fi, fr, en";
	const char *unknown;
	test_begin("fts language detect French");
	lp = fts_language_list_init(settings);
	test_assert(lp != NULL);
	test_assert(fts_language_list_add_names(lp, names, &unknown) == TRUE);
	test_assert(fts_language_detect(lp, french, sizeof(french)-1, &lang_r)
	            == FTS_LANGUAGE_RESULT_OK);
	test_assert(strcmp(lang_r->name, "fr") == 0);
	fts_language_list_deinit(&lp);
	test_end();
}
/* Detect German */
static void test_fts_language_detect_german(void)
{
	struct fts_language_list *lp = NULL;
	const struct fts_language *lang_r = NULL;
	const unsigned char german[]  =
		"Artikel 1"\
		"Alle Menschen sind frei und gleich an W\xC3\xBCrde und Rechten "\
		"geboren. Sie sind mit Vernunft und Gewissen begabt und sollen "\
		"einander im Geist der Br\xC3\xBC""derlichkeit begegnen." \
		"Artikel 2 Jeder hat Anspruch auf die in dieser "\
		"Erkl\xC3\xA4rung verk\xC3\xBCndeten Rechte und Freiheiten ohne"\
		"irgendeinen Unterschied, etwa nach Rasse, Hautfarbe, "\
		"Geschlecht, Sprache, Religion, politischer oder sonstiger "\
		"\xC3\x9C""berzeugung, nationaler oder sozialer Herkunft, "\
		"Verm\xC3\xB6gen, Geburt oder sonstigem Stand. Des weiteren "\
		"darf kein Unterschied gemacht werden auf Grund der "\
		"politischen, rechtlichen oder internationalen Stellung des "\
		"Landes oder Gebiets, dem eine Person angeh\xC3\xB6rt, "\
		"gleichg\xC3\xBCltig, ob dieses unabh\xC3\xA4ngig ist, unter "\
		"Treuhandschaft steht, keine Selbstregierung besitzt oder "\
		"sonst in seiner Souver\xC3\xA4nit\xC3\xA4t "\
		"eingeschr\xC3\xA4nkt ist.";



	const char names[] = "fi, de, fr, en";
	const char *unknown;
	test_begin("fts language detect German");
	lp = fts_language_list_init(settings);
	test_assert(lp != NULL);
	test_assert(fts_language_list_add_names(lp, names, &unknown) == TRUE);
	test_assert(fts_language_detect(lp, german, sizeof(german)-1, &lang_r)
	            == FTS_LANGUAGE_RESULT_OK);
	test_assert(strcmp(lang_r->name, "de") == 0);
	fts_language_list_deinit(&lp);
	test_end();
}

/* Detect Finnish as English */
static void test_fts_language_detect_finnish_as_english(void)
{
	struct fts_language_list *lp = NULL;
	const struct fts_language *lang_r = NULL;
	const unsigned char finnish[] =
		"Yhdistyneiden kansakuntien kolmas yleiskokous hyv\xC3\xA4ksyi "\
		"ja julkisti ihmisoikeuksien yleismaailmallisen julistuksen "\
		"joulukuun 10. p\xC3\xA4iv\xC3\xA4n\xC3\xA4 1948. Julistuksen "\
		"hyv\xC3\xA4ksymisen puolesta \xC3\xA4\xC3\xA4nesti 48 maata. "\
		"Mik\xC3\xA4\xC3\xA4n maa ei \xC3\xA4\xC3\xA4nest\xC3\xA4nyt "\
		"vastaan. Kahdeksan maata pid\xC3\xA4ttyi "\
		"\xC3\xA4\xC3\xA4nest\xC3\xA4m\xC3\xA4st\xC3\xA4.";
	const char names[] = "en";
	const char *unknown;
	test_begin("fts language detect Finnish as English");
	lp = fts_language_list_init(settings);
	test_assert(lp != NULL);
	test_assert(fts_language_list_add_names(lp, names, &unknown) == TRUE);
	test_assert(fts_language_detect(lp, finnish, sizeof(finnish)-1, &lang_r)
	            == FTS_LANGUAGE_RESULT_OK);
	test_assert(strcmp(lang_r->name, "en") == 0);
	fts_language_list_deinit(&lp);
	test_end();
}

/* Successfully avoid detecting English, when en is not in language list. */
static void test_fts_language_detect_na(void)
{
	struct fts_language_list *lp = NULL;
	const struct fts_language *lang_r = NULL;
	const unsigned char english[]  = "Whereas recognition of the inherent dignity and"\
		" of the equal and inalienable rights of all members of the human"\
		"family is the foundation of freedom, justice and peace in the "\
		"world,\n Whereas disregard and contempt for human rights have "\
		"resulted in barbarous acts which have outraged the conscience"\
		"of mankind, and the advent of a world in which human beings"\
		"shall enjoy freedom of speech and belief and freedom from "\
		"fear and want has been proclaimed as the highest aspiration"\
		"of the common people, ";

	const char names[] = "fi, de, fr";
	const char *unknown;
	test_begin("fts language detect not available");
	lp = fts_language_list_init(settings);
	test_assert(lp != NULL);
	test_assert(fts_language_list_add_names(lp, names, &unknown) == TRUE);
	test_assert(fts_language_detect(lp, english, sizeof(english)-1, &lang_r)
	            == FTS_LANGUAGE_RESULT_UNKNOWN);
	fts_language_list_deinit(&lp);
	test_end();
}

/* Successfully detect, that Klingon is unknown. */
static void test_fts_language_detect_unknown(void)
{
	struct fts_language_list *lp = NULL;
	const struct fts_language *lang_r = NULL;
	const unsigned char klingon[]  = "nobwI''a'pu'qoqvam'e' "\
		"nuHegh'eghrupqa'moHlaHbe'law'lI'neS "\
		"SeH'eghtaHghach'a'na'chajmo'.";

	const char names[] = "fi, de, fr";
	const char *unknown;
	test_begin("fts language detect unknown");
	lp = fts_language_list_init(settings);
	test_assert(lp != NULL);
	test_assert(fts_language_list_add_names(lp, names, &unknown) == TRUE);
	test_assert(fts_language_detect(lp, klingon, sizeof(klingon), &lang_r)
	            == FTS_LANGUAGE_RESULT_UNKNOWN);
	fts_language_list_deinit(&lp);
	test_end();
}

int main(void)
{
	static void (*test_functions[])(void) = {
		test_fts_language_detect_finnish,
		test_fts_language_detect_english,
		test_fts_language_detect_french,
		test_fts_language_detect_german,
		test_fts_language_detect_finnish_as_english,
		test_fts_language_detect_na,
		test_fts_language_detect_unknown,
		NULL
	};
	return test_run(test_functions);
}