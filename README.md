&nbsp;

&nbsp;

### This repository is deprecated. Smartcat now has a dedicated workflow, APIs and CLI to work with software localization projects. Check out our [Software Localization Projects in Smartcat](https://developers.smartcat.com/software-localization/) guide.

&nbsp;

&nbsp;

---

# Sample continuous localization project for a native Android application

This example project has everything you need to localize your native Android application on [Smartcat](https://smartcat.ai/) platform, using a fully automated *continuous localization* approach.

What we offer here is a pre-configured Docker container with our command-line localization automation tool, [Serge](https://serge.io/) _(String Extraction and Resource Generation Engine)_, which will pull the changes from your code repository, parse the source `strings.xml` file, send translation data over to Smartcat, get translations back, integrate them into its local database, generate localized files and push them back to your repo, all in a single sweep.

This approach to localization:

-   Doesn't require writing custom low-level integration code: you write declarative configuration files instead
-   Doesn't require you to change your CI/CD build process: translations are integrated statically into your source code repository
-   Is secure: you don't give Smartcat direct access to your source code repositories, and you control all the synchronization
-   Is vendor lock-in free: you own your translation data, and can generate localized resource files completely offline
-   Is flexible: you can manually run it on your computer, or run it on a schedule on a dedicated host
-   Is powerful: you can implement localization workflows that otherwise would require many months of development (see below).

## Features

With our continuous localization solution, you have an unprecedented flexibility and power. Some ideas that might inspire you are:

-   Automatic discovery and localization of multiple product branches
-   Ability to prohibit localized file updates unless they are 100% translated (handy for marketing materials!)
-   Ability to specify target languages right in each file, to enable automated self-service scenarios
-   Pseudo-localization for easier internationalization (i18n) QA
-   Conditional exclusion of certain strings by mask
-   Ability to auto-generate comments and preview links for each string
-   Ability to group multiple repositories and different file types under a same logical project
-   Ability to preprocess source files for greater flexibility
-   Ability to post-process localized files so that the final result is CI/CD-ready
-   Ability to email developers if source files are broken
-   ... and much more!

# Installation

1. [Install Docker](https://www.docker.com/products/docker-desktop) for your Windows, Mac, or Linux.

2. Run this command to install Serge for the first time, or to update it to a latest version:

       $ docker pull smartcatcom/serge

3. Clone this repository into any directory:

       $ git clone https://github.com/smartcatai/smartcat-serge-bootstrap-android-native.git

4. Create an account at [Smartcat.](https://www.smartcat.com/)
5. Create a new project in Smartcat to synchronize your data with, with _English_ as a source and _German_ and _Russian_ as target languages (don't worry, you will be able to change the settings later).

# Getting Started

## Running Serge in interactive mode

In the root directory of this repo we have provided you a convenience script to run a Serge shell, from which you will have access to `serge` command. Run it as follows (both under Windows, Mac or Linux):

    $ ./serge-shell

When you enter your shell, the root directory of your bootstrap project will be mounted as `/data` and you will see the following prompt:

    [Serge Shell] /data $

---

**Note:** Here and below, it is assumed that you're running the commands inside this shell. At the same time, you can continue editing the configuration files or browse the directory outside of the shell in Explorer, Finder, or any other favorite file management tool and code editor.

---

Now you that you are inside this interactive shell, you can run Serge (the command below will just show some short usage synopsis and a list of available commands):

    $ serge

To exit the shell later, use the `exit` command:

    $ exit

## Getting around

This repository contains a sample project, `android-native`. First things to do are:

-   See the configuration file: [configs/android-native.serge](configs/android-native.serge)
-   Look at the contents of the source project folder: [vcs/android-native](vcs/android-native)

This sample project is set up to have `en` (English) as a source language and `de` (German) and `ru` (Russian) as target languages, and will process all keys in the `strings.xml` resource file in [vcs/android-native/src/main/res/values](vcs/android-native/src/main/res/values) directory.

## Initial run

Go to the `configs` directory and run the localization step:

    $ cd configs
    $ serge localize

This will create localized files under `vcs/android-native/de` and `vcs/android-native/ru` directories. These files will have English content, since translations have not been provided just yet.

The same localization step will generate translation files under `ts/android-native/de` and `ts/android-native/ru` directories. You can examine the generated `.po` files and also see their initial state with no translations.

## Doing translations locally

Edit e.g. `ts/android-native/de/strings.xml.po` file and provide a translation for a single string (for testing purposes, any random "translation" will work).

Run `serge localize` once again from the `configs` directory. If you now open the localized resource file, e.g. `vcs/android-native/src/main/res/values-de/strings.xml`, you will see that your translation has been integrated into the XML file.

## Connecting with Smartcat

1. Create a new project in Smartcat with _English_ as a source language and _German_ and _Russian_ as target ones. Languages must be registered on the project before you can upload files targeting those languages. You can later change the list of target languages at any time.
2. Edit the [configs/common.serge.inc](configs/common.serge.inc) file and fill out your account parameters and credentials under _common-settings → ts_ config section: `base_url`, `account_id`, and `token`. Instructions next to each parameter will help you understand where to get the values from. Once defined, these settings will be shared across your future localization projects.
3. Edit the [configs/android-native.serge](configs/android-native.serge) file and specify the `project_id`, following the instructions in the configuration file.

Now you can push your translation files to Smartcat:

    $ serge push-ts

Go to Smartcat, open the test project you created, and there you will see your `strings.xml_de` and `strings.xml_ru` files available for translation, one for German, and another one for Russian.

Open e.g. `strings.xml_de` and edit the translation for the string that you translated previously.

Now you can pull translations from Smartcat and run a localization cycle at once:

    $ serge pull-ts localize

If you now open the localized resource file, `vcs/android-native/src/main/res/values-de/strings.xml`, you will see that the new translation has been integrated into the XML file.

## Running the localization continuously

This project has two convenience scripts, [sync-once.sh](sync-once.sh) and [sync-loop.sh](sync-loop.sh) that you can use as a starting point for your continuous localization process.

-   Run `./sync-once.sh` to run the sync/localization cycle just once.
-   Run `./sync-loop.sh` to run the sync/localization cycle every 5 minutes. You can edit the file and put any delay you want.

While the localization is running in background (eventually you will want to run it on a dedicated server), you can modify your example project (add, change or delete keys in your source XML file) and provide translations on Smartcat side at the same time, and Serge will merge in all these changes, gathering the new translations, updating the localized resources, and pushing new strings for translation.

## Adding VCS synchronization

The last missing step is to make Serge not only generate the localized files locally, but also pull the sources from your actual source code repository, and push localized files back to the remote repo. Since Git is the most popular version control system, this sample project includes a stub for connecting to a Git repo.

Edit the `configs/android-native.serge` file so that _→ sync → vcs → data →_ `remote_path` parameter points to the actual remote repository URL. Now initialize the data from the remote repo (this will remove the previous contents of `vcs/android-native` folder with the contents of your repository):

    $ serge pull --initialize android-native.serge

The `--initialize` parameter in this command is needed only once, when you want to delete and re-populate the contents of the project folder.

Now your project has a different directory structure, and maybe different files (not JSON), so you need to edit your `configs/android-native.serge` file accordingly (see _→ jobs → (first job section) →_ `source_dir`, `source_match`, `output_file_path` parameters, and the `parser` section). At this point we recommend you to spend some time reading the [Serge documentation](https://serge.io/docs/) for the list of available parsers and their parameters, and the [configuration file syntax and reference](https://serge.io/docs/configuration-files/syntax/).

Once you have your job parameters tweaked, it's time to test this by running a localization cycle once again, and also cleaning up the outdated translation files:

    $ serge localize
    $ serge clean-ts

If you see that a set of localized files was properly created in your `vcs/android-native` folder, and that translation files in `ts/android-native` folder also look good, you can push the localized files back to the remote repository:

    $ serge push

The last and final step is to enable the full synchronization cycle. Edit the `sync-once.sh` script by disabling the `serge pull-ts localize push-ts` line and enabling the `serge sync` line. The latter command is equivalent to `serge pull pull-ts localize push-ts push`. In human language, this means that running `serge sync` will do everything a continuous localization is expected to do: pull the new contents from both your Git server and Smartcat, update localized resources and translation files, and push changes back to Git and Smartcat, respectively.

Finally, run:

```
./sync-loop.sh
```

Congratulations! You now live in the world of smooth continuous localization _(press Ctrl+C anytime to get back to reality)_.

## Running Serge in a non-interactive mode

When you don't need an interactive shell (especially when you're running Serge on a dedicated server), you can use a provided `run-in-docker` wrapper, as follows:

    $ ./run-in-docker serge localize configs/android-native.serge

or:

    $ ./run-in-docker ./sync-loop.sh

## Adding new projects

In the paradigm of continuous localization, your Smartcat projects will be permanent; content in these projects will be constantly updated, reflecting the changes in your repositories and external content sources. You can create one project for your iOS application, another one for Android, for your website, documentation, and so on. To set up a new project (besides creating one in Smartcat), you will need to make a copy of `configs/android-native.serge` to `configs/project-b.serge` (of course, file and project names are up to you), and edit a new configuration file accordingly.

## Getting professional support

At Smartcat, we strive to build delightful localization processes that work seamlessly and don't slow you down. We offer managed solutions and localization engineering services [as a part of the subscription](https://www.smartcat.com/pricing/), so you don't have to figure this out all by yourself!</p>
