// ----------------------- Variable Globales ------------------------ //
const int character_bitmap[9][13] =
{
   { 1,1,1,2,2,2,2,2,2,2,2,1,1 },
   { 1,0,0,1,2,2,2,2,2,2,1,0,1 },
   { 1,0,0,0,1,2,2,2,2,1,0,0,1 },
   { 1,0,0,0,0,1,2,1,1,1,0,1,2 },
   { 2,1,0,0,0,0,1,0,0,0,1,2,2 },
   { 2,1,1,1,0,0,0,0,1,0,1,1,2 },
   { 2,1,0,1,0,1,1,0,0,0,1,2,2 },
   { 2,2,1,1,1,0,0,0,0,1,2,2,2 },
   { 2,2,2,2,1,1,1,1,1,2,2,2,2 }
};


const int pipelines_bitmap[3][64][13] =
{
   {
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 }
   },

   {
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 }
   },

   {
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 2,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 2,2,1,1,1,1,1,1,1,1,1,2,2 }
   }
};