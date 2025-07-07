
void printf(char* str)
{
  unsigned short* videoMemory = (unsigned short*) 0xb8000;
    for (int i = 0; str[i] != '\0'; ++i)
  {
    videoMemory[i] = (videoMemory[i]& 0xFF00) | str[i];

  }
}

typedef void (*constructor)();
constructor start_ctors;
constructor end_ctors;
void callConstructors()
{
  for(constructor* i = &start_ctors; i != end_ctors; i++)
  {
    (*i)();
  }
}

void kernelMain(void* multiboot_struction, unsigned int magicNumber)
{
  printf("hello world");
  while(1);
}
