## Generating a Binary Message Catalog

Follow these steps to create and install a `.mo` translation file for your source code:

1. **Extract Translatable Strings:**

   Extract all translatable strings from your source code and save them in a Portable Object Template (`.pot`) file:

   ```bash
   xgettext --extract-all --c++ --output=locale_demo.pot main.cpp
   ```

2. **Edit the `.pot` File:**

   Open the generated `.pot` file and remove any untranslatable or unnecessary entries. This file can be added to version control so other translators can contribute. Here’s an example of what the `.pot` file might look like:

   ```bash
   # locale_demo.pot

   # SOME DESCRIPTIVE TITLE.
   # Copyright (C) YEAR THE PACKAGE'S COPYRIGHT HOLDER
   # This file is distributed under the same license as the PACKAGE package.
   # FIRST AUTHOR <EMAIL@ADDRESS>, YEAR.
   #
   #: main.cpp:25 main.cpp:31
   #, fuzzy
   msgid ""
   msgstr ""
   "Project-Id-Version: PACKAGE VERSION\n"
   "Report-Msgid-Bugs-To: \n"
   "POT-Creation-Date: 2024-08-11 00:34+0000\n"
   "PO-Revision-Date: YEAR-MO-DA HO:MI+ZONE\n"
   "Last-Translator: FULL NAME <EMAIL@ADDRESS>\n"
   "Language-Team: LANGUAGE <LL@li.org>\n"
   "Language: \n"
   "MIME-Version: 1.0\n"
   "Content-Type: text/plain; charset=CHARSET\n"
   "Content-Transfer-Encoding: 8bit\n"

   #: main.cpp:64
   msgid "Really quit configuration?"
   msgstr ""

   #: main.cpp:65
   msgid "yes"
   msgstr ""

   #: main.cpp:66
   msgid "no"
   msgstr ""
   ```

3. **Create a `.po` File:**

   Fill in the header information and provide translations for each string. Save this file with a `.po` extension. Here’s an example:

   ```bash
   # locale_demo.po

   # SOME DESCRIPTIVE TITLE.
   # Copyright (C) YEAR THE PACKAGE'S COPYRIGHT HOLDER
   # This file is distributed under the same license as the PACKAGE package.
   # FIRST AUTHOR <EMAIL@ADDRESS>, YEAR.
   #
   #: main.cpp:25 main.cpp:31
   #, fuzzy
   msgid ""
   msgstr ""
   "Project-Id-Version: PACKAGE VERSION\n"
   "Report-Msgid-Bugs-To: \n"
   "POT-Creation-Date: 2024-08-11 00:34+0000\n"
   "PO-Revision-Date: YEAR-MO-DA HO:MI+ZONE\n"
   "Last-Translator: FULL NAME <EMAIL@ADDRESS>\n"
   "Language-Team: Malay <LL@li.org>\n"
   "Language: \n"
   "MIME-Version: 1.0\n"
   "Content-Type: text/plain; charset=UTF-8\n"
   "Content-Transfer-Encoding: 8bit\n"

   #: main.cpp:64
   msgid "Really quit configuration?"
   msgstr "Benar-benar mahu keluar daripada konfigurasi?"

   #: main.cpp:65
   msgid "yes"
   msgstr "Ya"

   #: main.cpp:66
   msgid "no"
   msgstr "Tidak"
   ```

4. **Generate the `.mo` File:**

   Compile the `.po` file into a binary `.mo` file:

   ```bash
   msgfmt --check --output-file=locale_demo.mo locale_demo.po
   ```

5. **Install the `.mo` File:**

   Place the generated `.mo` file in the appropriate directory on your system:

   ```bash
   sudo cp locale_demo.mo /usr/share/locale/ms/LC_MESSAGES/
   ```

This process will enable your software to support multiple languages by using translation files.
