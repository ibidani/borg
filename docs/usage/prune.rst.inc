.. IMPORTANT: this file is auto-generated from borg's built-in help, do not edit!

.. _borg_prune:

borg prune
----------
.. code-block:: none

    borg [common options] prune [options]

.. only:: html

    .. class:: borg-options-table

    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    | **optional arguments**                                                                                                                                                                                                            |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``-n``, ``--dry-run``                             | do not change repository                                                                        |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``--force``                                       | force pruning of corrupted archives, use ``--force --force`` in case ``--force`` does not work. |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``-s``, ``--stats``                               | print statistics for the deleted archive                                                        |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``--list``                                        | output verbose list of archives it keeps/prunes                                                 |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``--keep-within INTERVAL``                        | keep all archives within this time interval                                                     |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``--keep-last``, ``--keep-secondly``              | number of secondly archives to keep                                                             |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``--keep-minutely``                               | number of minutely archives to keep                                                             |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``-H``, ``--keep-hourly``                         | number of hourly archives to keep                                                               |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``-d``, ``--keep-daily``                          | number of daily archives to keep                                                                |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``-w``, ``--keep-weekly``                         | number of weekly archives to keep                                                               |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``-m``, ``--keep-monthly``                        | number of monthly archives to keep                                                              |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``-y``, ``--keep-yearly``                         | number of yearly archives to keep                                                               |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``--save-space``                                  | work slower, but using less space                                                               |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``-c SECONDS``, ``--checkpoint-interval SECONDS`` | write checkpoint every SECONDS seconds (Default: 1800)                                          |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    | .. class:: borg-common-opt-ref                                                                                                                                                                                                    |
    |                                                                                                                                                                                                                                   |
    | :ref:`common_options`                                                                                                                                                                                                             |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    | **Archive filters** — Archive filters can be applied to repository targets.                                                                                                                                                       |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+
    |                                                                             | ``-a PATTERN``, ``--match-archives PATTERN``      | only consider archive names matching the pattern. see "borg help match-archives".               |
    +-----------------------------------------------------------------------------+---------------------------------------------------+-------------------------------------------------------------------------------------------------+

    .. raw:: html

        <script type='text/javascript'>
        $(document).ready(function () {
            $('.borg-options-table colgroup').remove();
        })
        </script>

.. only:: latex



    optional arguments
        -n, --dry-run         do not change repository
        --force               force pruning of corrupted archives, use ``--force --force`` in case ``--force`` does not work.
        -s, --stats           print statistics for the deleted archive
        --list                output verbose list of archives it keeps/prunes
        --keep-within INTERVAL    keep all archives within this time interval
        --keep-last, --keep-secondly    number of secondly archives to keep
        --keep-minutely       number of minutely archives to keep
        -H, --keep-hourly     number of hourly archives to keep
        -d, --keep-daily      number of daily archives to keep
        -w, --keep-weekly     number of weekly archives to keep
        -m, --keep-monthly    number of monthly archives to keep
        -y, --keep-yearly     number of yearly archives to keep
        --save-space          work slower, but using less space
        -c SECONDS, --checkpoint-interval SECONDS    write checkpoint every SECONDS seconds (Default: 1800)


    :ref:`common_options`
        |

    Archive filters
        -a PATTERN, --match-archives PATTERN     only consider archive names matching the pattern. see "borg help match-archives".


Description
~~~~~~~~~~~

The prune command prunes a repository by deleting all archives not matching
any of the specified retention options.

Important: Repository disk space is **not** freed until you run ``borg compact``.

This command is normally used by automated backup scripts wanting to keep a
certain number of historic backups. This retention policy is commonly referred to as
`GFS <https://en.wikipedia.org/wiki/Backup_rotation_scheme#Grandfather-father-son>`_
(Grandfather-father-son) backup rotation scheme.

Also, prune automatically removes checkpoint archives (incomplete archives left
behind by interrupted backup runs) except if the checkpoint is the latest
archive (and thus still needed). Checkpoint archives are not considered when
comparing archive counts against the retention limits (``--keep-X``).

If you use --match-archives (-a), then only archives that match the pattern are
considered for deletion and only those archives count towards the totals
specified by the rules.
Otherwise, *all* archives in the repository are candidates for deletion!
There is no automatic distinction between archives representing different
contents. These need to be distinguished by specifying matching globs.

If you have multiple sequences of archives with different data sets (e.g.
from different machines) in one shared repository, use one prune call per
data set that matches only the respective archives using the --match-archives
(-a) option.

The ``--keep-within`` option takes an argument of the form "<int><char>",
where char is "H", "d", "w", "m", "y". For example, ``--keep-within 2d`` means
to keep all archives that were created within the past 48 hours.
"1m" is taken to mean "31d". The archives kept with this option do not
count towards the totals specified by any other options.

A good procedure is to thin out more and more the older your backups get.
As an example, ``--keep-daily 7`` means to keep the latest backup on each day,
up to 7 most recent days with backups (days without backups do not count).
The rules are applied from secondly to yearly, and backups selected by previous
rules do not count towards those of later rules. The time that each backup
starts is used for pruning purposes. Dates and times are interpreted in
the local timezone, and weeks go from Monday to Sunday. Specifying a
negative number of archives to keep means that there is no limit. As of borg
1.2.0, borg will retain the oldest archive if any of the secondly, minutely,
hourly, daily, weekly, monthly, or yearly rules was not otherwise able to meet
its retention target. This enables the first chronological archive to continue
aging until it is replaced by a newer archive that meets the retention criteria.

The ``--keep-last N`` option is doing the same as ``--keep-secondly N`` (and it will
keep the last N archives under the assumption that you do not create more than one
backup archive in the same second).

When using ``--stats``, you will get some statistics about how much data was
deleted - the "Deleted data" deduplicated size there is most interesting as
that is how much your repository will shrink.
Please note that the "All archives" stats refer to the state after pruning.