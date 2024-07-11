#include <Novice.h>
#include<Vector3.h>
#include<Matrix4x4.h>
#include<imgui.h>
#include<cmath>

const char kWindowTitle[] = "LD2B_04_コマツザキ_カガリ_タイトル";


// 関数のプロトタイプ宣言
// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2);
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
// スカラー倍
Vector3 Multiply(float k, const Vector3& v1);
// X軸回転行列
Matrix4x4 MakeRotateXMatrix(const Vector3& rotate);
// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(Vector3 rotate);
// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(Vector3 rotate);
// XYZ合成
Matrix4x4 MultiplyXYZ(const Matrix4x4& rotateX, const Matrix4x4& rotateYZ);

// 二項演算子
Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
Vector3 operator*(float s, const Vector3& v) { return Multiply(s, v); }
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return MultiplyXYZ(m1, m2); }



// 関数の定義
// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 add{};
	add.x = v1.x + v2.x;
	add.y = v1.y + v2.y;
	add.z = v1.z + v2.z;
	return add;
}

// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 subtract{};
	subtract.x = v1.x - v2.x;
	subtract.y = v1.y - v2.y;
	subtract.z = v1.z - v2.z;
	return subtract;
}

// スカラー倍
Vector3 Multiply(float k, const Vector3& v1)
{
	Vector3 multiply{};
	multiply.x = k * v1.x;
	multiply.y = k * v1.y;
	multiply.z = k * v1.z;
	return multiply;
}

// X軸回転行列
Matrix4x4 MakeRotateXMatrix(float rotate)
{
	Matrix4x4 result{};

	result.m[1][1] = std::cos(rotate);
	result.m[1][2] = std::sin(rotate);
	result.m[2][1] = -std::sin(rotate);
	result.m[2][2] = std::cos(rotate);
	result.m[0][0] = 1;
	result.m[3][3] = 1;

	return result;
}

// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float rotate)
{
	Matrix4x4 result{};

	result.m[0][0] = std::cos(rotate);
	result.m[0][2] = -std::sin(rotate);
	result.m[1][1] = 1;
	result.m[2][0] = std::sin(rotate);
	result.m[2][2] = std::cos(rotate);
	result.m[3][3] = 1;

	return result;
}

// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float rotate)
{
	Matrix4x4 result{};

	result.m[0][0] = std::cos(rotate);
	result.m[0][1] = std::sin(rotate);
	result.m[1][0] = -std::sin(rotate);
	result.m[1][1] = std::cos(rotate);
	result.m[2][2] = 1;
	result.m[3][3] = 1;

	return result;
}

// XYZ合成
Matrix4x4 MultiplyXYZ(const Matrix4x4& rotateX, const Matrix4x4& rotateYZ)
{
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result.m[i][j] += rotateX.m[i][k] * rotateYZ.m[k][j];
			}
		}
	}

	return result;
}



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	Vector3 a{ 0.2f,1.0f,0.0f };
	Vector3 b{ 2.4f,3.1f,1.2f };
	Vector3 c = operator+(a, b);
	Vector3 d = operator-(a, b);
	Vector3 e = operator*(2.4f, a);
	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYMatrix = operator*(rotateXMatrix, rotateYMatrix);
	Matrix4x4 rotateXYZMatrix = operator*(rotateXYMatrix, rotateZMatrix);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		ImGui::Begin("Window");
		ImGui::Text("c:%f, %f, %f", c.x, c.y, c.z);
		ImGui::Text("d:%f, %f, %f", d.x, d.y, d.z);
		ImGui::Text("e:%f, %f, %f", e.x, e.y, e.z);
		ImGui::Text(
			"matrix:\n%f, %f, %f, %f\n\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
			rotateXYZMatrix.m[0][0], rotateXYZMatrix.m[0][1], rotateXYZMatrix.m[0][2],
			rotateXYZMatrix.m[0][3], rotateXYZMatrix.m[1][0], rotateXYZMatrix.m[1][1],
			rotateXYZMatrix.m[1][2], rotateXYZMatrix.m[1][3], rotateXYZMatrix.m[2][0],
			rotateXYZMatrix.m[2][1], rotateXYZMatrix.m[2][2], rotateXYZMatrix.m[2][3],
			rotateXYZMatrix.m[3][0], rotateXYZMatrix.m[3][1], rotateXYZMatrix.m[3][2],
			rotateXYZMatrix.m[3][3]
		);
		ImGui::End();


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
