common-settings
{
    ts
    {
        plugin                                  smartcat_v2

        data
        {
            /*
            Provide the base API server URL here.
            Note that the trailing slash must be omitted.
            Options are:
            https://smartcat.ai       (Europe)
            https://us.smartcat.ai    (North America)
            https://ea.smartcat.ai    (Asia)
            You will know the server your account is on
            by just signing into your account
            and looking at the URL.
            */
            base_url                            https://smartcat.ai

            /*
            Provide your account ID as it is displayed on
            your `Settings > API` page once you sign into
            your Smartcat account.
            */
            account_id                          12345678-abcd-9876-5432-abcdef012345

            /*
            Go to `Settings > API` page in your account,
            and generate an API key. Key name can be anything,
            e.g. 'Serge', and the auto-generated secret part
            of the key is what needs to be added here.
            */
            token                               1_AaBbCcDdEeFfGgHhIiJjKkLlM

            /*
            [OPTIONAL] Enable debug mode if requested by Smartcat support.
            */
            #debug                               YES
        }
    }

    vcs
    {
        plugin                                  git

        data
        {
            add_unversioned                     YES
            clone_params                        --depth 1
            email                               l10n@mycompany.com
            name                                L10N Robot
        }
    }

    job
    {
        /*
        Usually you want to have a single database for all your
        translation projects, unless you have multiple source languages.
        In that case it is recommended to split databases for each
        source language.
        */
        db_source                               DBI:SQLite:dbname=../db/translate.db3

        /*
        Source language must be recognized by Smartcat.
        See https://smartcat.ai/Home/Languages
        */
        source_language                         en
        output_bom                              NO
        use_keys_as_context                     YES

        callback_plugins
        {
            /*
            Currently Smartcat expects a flat list of .po files
            in each language directory, i.e. it doesn't support
            subdirectories in its projects.
            The code below will flatten output file paths
            by replacing `/` with a custom separator, `--`.
            */
            :flatten-ts-file-path
            {
                plugin                          replace_strings
                phase                           rewrite_relative_ts_file_path

                data
                {
                    replace                     `\/` `--` g
                }
            }
        }
    }
}