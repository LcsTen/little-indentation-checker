# Little Indentation Checker

Little Indentation Checker is a minimalist program that check if a source file
is indented with the correct characters, ie either spaces or tabulations.
He isn't sophisticated and doesn't understand the language of the input files.
As such, he doesn't check if the number of indentations is correct.

Little Indentation Checker has three modes:
- Tabulations: The files should be indented only with tabulations, except for
some final spaces, as long as there are less than 8. That last part is useful to
align a line with the previous line, but may imply false negatives.
- Strict tabulations: The files should be indented only with tabulations,
without any spaces. This nullify the chance of false negatives from the previous
mode, but you won't be able to align lines with spaces.
- Spaces: The files should be indented only with spaces.

## Usage

```
little-indentation-checker [--tab|--tab-strict|--spaces] [--] [input-files...]
```
