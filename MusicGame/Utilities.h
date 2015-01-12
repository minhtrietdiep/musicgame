int GetIndex(char *input, char character)
{
	const char *indexptr = strchr(input, character);
	if (indexptr) {
		return indexptr - input;
	}
	else
	{
		return -1;
	}
}