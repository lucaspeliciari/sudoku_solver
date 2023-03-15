void reset(int* &possibleAnswers)
{
    for (int i = 0; i < 9; i++) possibleAnswers[i] = i+1;
}

int length(int* &possibleAnswers)
{
    int length = 0;
    for (int i = 0; i < 9; i++) 
        if (possibleAnswers[i] != -1) 
            length++;
    return length;
}

int get(int* &possibleAnswers, int randomIndex = -1)
{
    int currentIndex = 0;
    for (int i = 0; i < 9; i++) 
        if (possibleAnswers[i] != -1) 
        {
            if (randomIndex == -1)
                return possibleAnswers[i];
            else
            {
                if (currentIndex == randomIndex) return possibleAnswers[i];
                else currentIndex++;
            }
        }
            
    return 0;
}