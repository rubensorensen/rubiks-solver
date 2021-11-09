#include "Patterns.h"
#include "Cube.h"

void Patterns::Superflip(Cube& cube)
{
	cube.U();
	cube.R2();
	cube.F();
	cube.B();
	cube.R();
	cube.B2();
	cube.R();
	cube.U2();
	cube.L();
	cube.B2();
	cube.R();
	cube.Uprime();
	cube.Dprime();
	cube.R2();
	cube.F();
	cube.Rprime();
	cube.L();
	cube.B2();
	cube.U2();
	cube.F2();
}


void Patterns::Checkerboard(Cube& cube)
{
	cube.R2();
	cube.L2();
	cube.F2();
	cube.B2();
	cube.U2();
	cube.D2();
}

void Patterns::Wire(Cube& cube)
{
	cube.R();
	cube.L();
	cube.F();
	cube.B();
	cube.R();
	cube.L();
	cube.F();
	cube.B();
	cube.R();
	cube.L();
	cube.F();
	cube.B();
	cube.R2();
	cube.B2();
	cube.L2();
	cube.R2();
	cube.B2();
	cube.L2();
}

void Patterns::CheckerboardInCube(Cube& cube)
{
	cube.B();
	cube.D();
	cube.Fprime();
	cube.Bprime();
	cube.D();
	cube.L2();
	cube.U();
	cube.L();
	cube.Uprime();
	cube.B();
	cube.Dprime();
	cube.R();
	cube.B();
	cube.R();
	cube.Dprime();
	cube.R();
	cube.Lprime();
	cube.F();
	cube.U2();
	cube.D();
}

void Patterns::PerpendicularLines(Cube& cube)
{
	cube.R2();
	cube.U2();
	cube.L2();
	cube.R2();
	cube.U2();
	cube.R2();
}

void Patterns::FlippedTips(Cube& cube)
{
	cube.U();
	cube.B();
	cube.Dprime();
	cube.F2();
	cube.D();
	cube.Bprime();
	cube.Uprime();
	cube.R2();
	cube.D();
	cube.F2();
	cube.Dprime();
	cube.R2();
	cube.D();
	cube.F2();
	cube.Dprime();
	cube.R2();
}

void Patterns::Spiral(Cube& cube)
{
	cube.Lprime();
	cube.Bprime();
	cube.D();
	cube.U();
	cube.R();
	cube.Uprime();
	cube.Rprime();
	cube.D2();
	cube.R2();
	cube.D();
	cube.L();
	cube.Dprime();
	cube.Lprime();
	cube.Rprime();
	cube.F();
	cube.U();
}

void Patterns::Deckerboard(Cube& cube)
{
	cube.U();
	cube.D();
	cube.R();
	cube.Lprime();		
	cube.Fprime();
	cube.B();
	cube.U();
	cube.Dprime();
	cube.R2();
	cube.U();
	cube.R2();
	cube.L2();
	cube.D2();
	cube.F2();
	cube.B2();
	cube.D();
}

void Patterns::VerticalLines(Cube& cube)
{
	cube.F();
	cube.U();
	cube.F();
	cube.R();
	cube.L2();
	cube.B();
	cube.Dprime();
	cube.R();
	cube.D2();
	cube.L();
	cube.Dprime();
	cube.B();
	cube.R2();
	cube.L();
	cube.F();
	cube.U();
	cube.F();
}

void Patterns::Crosses(Cube& cube)
{
	cube.R2();
	cube.Lprime();
	cube.D();
	cube.F2();
	cube.Rprime();
	cube.Dprime();
	cube.Rprime();
	cube.L();
	cube.Uprime();
	cube.D();
	cube.R();
	cube.D();
	cube.B2();
	cube.Rprime();
	cube.U();
	cube.D2();
}

void Patterns::CubeInCube(Cube& cube)
{
	cube.F();
	cube.L();
	cube.F();
	cube.Uprime();
	cube.R();
	cube.U();
	cube.F2();
	cube.L2();
	cube.Uprime();
	cube.Lprime();
	cube.B();
	cube.Dprime();
	cube.Bprime();
	cube.L2();
	cube.U();
}

void Patterns::CubeInCubeInCube(Cube& cube)
{
	cube.Uprime();
	cube.Lprime();
	cube.Uprime();
	cube.Fprime();
	cube.R2();
	cube.Bprime();
	cube.R();
	cube.F();
	cube.U();
	cube.B2();
	cube.U();
	cube.Bprime();
	cube.L();
	cube.Uprime();
	cube.F();
	cube.U();
	cube.R();
	cube.Fprime();
}

void Patterns::Anaconda(Cube& cube)
{
	cube.L();
	cube.U();
	cube.Bprime();
	cube.Uprime();
	cube.R();
	cube.Lprime();
	cube.B();
	cube.Rprime();
	cube.F();
	cube.Bprime();
	cube.D();
	cube.R();
	cube.Dprime();
	cube.Fprime();
}

void Patterns::Python(Cube& cube)
{
	cube.F2();
	cube.Rprime();
	cube.Bprime();
	cube.U();
	cube.Rprime();
	cube.L();
	cube.Fprime();
	cube.L();
	cube.Fprime();
	cube.B();
	cube.Dprime();
	cube.R();
	cube.B();
	cube.L2();
}

void Patterns::Spots(Cube& cube)
{
	cube.U();
	cube.Dprime();
	cube.R();
	cube.Lprime();
	cube.F();
	cube.Bprime();
	cube.U();
	cube.Dprime();
}

