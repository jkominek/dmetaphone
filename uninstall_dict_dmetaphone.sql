
-- Adjust this setting to control where the objects get dropped.
SET search_path = public;

DROP TEXT SEARCH DICTIONARY dmetaphonedict;

DROP TEXT SEARCH TEMPLATE dmetaphonedict_template;

DROP FUNCTION ddmetaphonedict_init(internal);

DROP FUNCTION ddmetaphonedict_lexize(internal,internal,internal,internal);
