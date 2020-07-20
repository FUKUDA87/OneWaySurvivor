xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 82;
 0.00000;0.00350;0.00000;,
 0.01419;0.00350;-0.01419;,
 0.00000;0.00350;-0.02006;,
 0.02006;0.00350;0.00000;,
 0.01419;0.00350;0.01419;,
 -0.00000;0.00350;0.02006;,
 -0.01419;0.00350;0.01419;,
 -0.02006;0.00350;-0.00000;,
 -0.01419;0.00350;-0.01419;,
 0.01554;-0.00910;-0.01554;,
 0.00000;-0.00910;-0.02198;,
 0.02198;-0.00910;0.00000;,
 0.01554;-0.00910;0.01554;,
 -0.00000;-0.00910;0.02198;,
 -0.01554;-0.00910;0.01554;,
 -0.02198;-0.00910;-0.00000;,
 -0.01554;-0.00910;-0.01554;,
 0.01669;-0.04497;-0.01669;,
 0.00000;-0.04497;-0.02361;,
 0.02361;-0.04497;0.00000;,
 0.01669;-0.04497;0.01669;,
 -0.00000;-0.04497;0.02361;,
 -0.01669;-0.04497;0.01669;,
 -0.02361;-0.04497;-0.00000;,
 -0.01669;-0.04497;-0.01669;,
 0.01746;-0.09865;-0.01746;,
 0.00000;-0.09865;-0.02470;,
 0.02470;-0.09865;0.00000;,
 0.01746;-0.09865;0.01746;,
 -0.00000;-0.09865;0.02470;,
 -0.01746;-0.09865;0.01746;,
 -0.02470;-0.09865;-0.00000;,
 -0.01746;-0.09865;-0.01746;,
 0.01773;-0.16197;-0.01773;,
 0.00000;-0.16197;-0.02508;,
 0.02508;-0.16197;0.00000;,
 0.01773;-0.16197;0.01773;,
 -0.00000;-0.16197;0.02508;,
 -0.01773;-0.16197;0.01773;,
 -0.02508;-0.16197;-0.00000;,
 -0.01773;-0.16197;-0.01773;,
 0.01773;-1.48573;-0.01773;,
 0.00000;-1.48573;-0.02508;,
 0.02508;-1.48573;0.00000;,
 0.01773;-1.48573;0.01773;,
 -0.00000;-1.48573;0.02508;,
 -0.01773;-1.48573;0.01773;,
 -0.02508;-1.48573;-0.00000;,
 -0.01773;-1.48573;-0.01773;,
 0.11165;-1.54905;-0.11678;,
 0.00000;-1.54905;-0.16515;,
 0.15790;-1.54905;0.00000;,
 0.11165;-1.54905;0.11678;,
 -0.00000;-1.54905;0.16515;,
 -0.11165;-1.54905;0.11678;,
 -0.15790;-1.54905;-0.00000;,
 -0.11165;-1.54905;-0.11678;,
 0.10674;-1.60273;-0.11164;,
 0.00000;-1.60273;-0.15788;,
 0.15095;-1.60273;0.00000;,
 0.10674;-1.60273;0.11164;,
 -0.00000;-1.60273;0.15788;,
 -0.10674;-1.60273;0.11164;,
 -0.15095;-1.60273;-0.00000;,
 -0.10674;-1.60273;-0.11164;,
 0.09938;-1.63860;-0.10395;,
 0.00000;-1.63860;-0.14700;,
 0.14055;-1.63860;0.00000;,
 0.09938;-1.63860;0.10395;,
 -0.00000;-1.63860;0.14700;,
 -0.09938;-1.63860;0.10395;,
 -0.14055;-1.63860;-0.00000;,
 -0.09938;-1.63860;-0.10395;,
 0.09070;-1.65120;-0.09487;,
 0.00000;-1.65120;-0.13417;,
 0.12828;-1.65120;0.00000;,
 0.09070;-1.65120;0.09487;,
 -0.00000;-1.65120;0.13417;,
 -0.09070;-1.65120;0.09487;,
 -0.12828;-1.65120;-0.00000;,
 -0.09070;-1.65120;-0.09487;,
 0.00000;-1.65120;-0.00000;;
 
 88;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 3;74,73,81;,
 3;73,75,81;,
 3;75,76,81;,
 3;76,77,81;,
 3;77,78,81;,
 3;78,79,81;,
 3;79,80,81;,
 3;80,74,81;;
 
 MeshMaterialList {
  1;
  88;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
}