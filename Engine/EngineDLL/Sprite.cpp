#include "Sprite.h"

Sprite::Sprite(Renderer* renderer, int _cantFrames) : Shape(renderer) {
	collision = false;
	
	animation = new Animation(_cantFrames);
	// OLD 
	/*vertex = new float[12]{													
		-1.0f, -1.0f, 0.0f,													
		-1.0f, 1.0f, 0.0f,													
		1.0f, -1.0f, 0.0f,													
		1.0f, 1.0f, 0.0f										
	};*/
	vertex = new float[12] {
		-1.0f,-1.0f , 0.0f ,
		1.0f,-1.0f , 0.0f ,
		-1.0f, 1.0f , 0.0f ,
		1.0f, 1.0f , 0.0f
	};


	//UVBufferID = -1;

	/*textureVertex = new float[8]{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};*/

	SetVertices(vertex, 4);

	textureVertex = animation->UpdateFrame();

	SetTextureVertices(4);
}

void Sprite::LoadBMP(const char * name) {
	header = Importer::LoadBMP(name);
	textureId = renderer->UploadData(header.width, header.height, header.data);
	material->BindTexture();
}

unsigned int Sprite::LoadTexture(const char* _name) {
	header = Importer::LoadBMP(_name);

	return renderer->GenTextureBuffer(header.width, header.height, header.data);
}

void Sprite::SetTextureVertices(int count) {
	DisposeTexture();

	vtxTextureCount = count;
	shouldDisposeTexture = true;

	txrBufferId = renderer->GenBuffer(textureVertex, sizeof(float) * count * 2);
}

void Sprite::SetTextureVertices(float* _vertex, int _cant) {
	DisposeTexture();

	txrBufferId = renderer->GenBuffer(_vertex, sizeof(float)* _cant * 2);
	//dispouse = true;
}

void Sprite::DrawMesh1(int type) {
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(worldMatrix);

	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty(renderer->GetWVP());
		//material->BindTexture("myTextureSampler", UVBufferID);
	}
	//renderer->BindTexture(textureId, txrBufferId);
	renderer->BeginDraw(0);
	renderer->BeginDraw(1);																	// Le decimos al renderer que comience a dibujar
	renderer->BindBuffer(bufferId, 0);
	renderer->BindTextureBuffer(txrBufferId, 1);											// Unimos el buffer con el buffer binding point
	renderer->DrawBuffer(vtxCount, type);													// El renderer dibuja el triangulo
	renderer->EndDraw(0);
	renderer->EndDraw(1);																	// Deja de dibujar
}

void Sprite::SetTextureBufferId(unsigned int _textureBufferId) {
	UVBufferID = _textureBufferId;
}

void Sprite::DisposeTexture() {
	if (shouldDisposeTexture) {
		renderer->DestroyBuffer(txrBufferId);
		shouldDisposeTexture = false;
	}
}

void Sprite::Draw() {
	DrawMesh1(GL_TRIANGLE_STRIP);
}

Sprite::~Sprite() {
	delete[] vertex;
	delete[] textureVertex;
}

void Sprite::SetMaterial(Material* material) {
	this->material = material;
}

void Sprite::UpdateAnim() {
	textureVertex = animation->UpdateFrame();
	//SetTextureVertices(4);
	SetTextureVertices(textureVertex, 4);
}