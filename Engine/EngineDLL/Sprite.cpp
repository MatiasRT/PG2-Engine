#include "Sprite.h"

Sprite::Sprite(Renderer* renderer, int frames, const char* filename) : Shape(renderer) {
	collision = false;
	
	file = filename;

	animation = new Animation(frames);

	vertex = new float[12] {
		-1.0f,-1.0f , 0.0f ,
		1.0f,-1.0f , 0.0f ,
		-1.0f, 1.0f , 0.0f ,
		1.0f, 1.0f , 0.0f
	};

	SetVertices(vertex, 4);

	textureVertex = animation->UpdateFrame();

	SetTextureVertices(textureVertex, 4);
}

void Sprite::LoadBMP(const char * name) {
	header = Importer::LoadBMP(name);
	textureId = renderer->UploadData(header.width, header.height, header.data);
	material->BindTexture();
}

unsigned int Sprite::LoadTexture(const char* name) {
	header = Importer::LoadBMP(name);
	return renderer->GenTextureBuffer(header.width, header.height, header.data);
}

void Sprite::SetTextureVertices(float* vertex, int cant) {
	DisposeTexture();

	vtxTextureCount = cant;
	shouldDisposeTexture = true;

	txrBufferId = renderer->GenBuffer(vertex, sizeof(float)* cant * 2);
}

void Sprite::DrawMesh1(int type) {
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(worldMatrix);

	if (material != NULL) {
		material->Bind(file, UVBufferID);
		material->SetMatrixProperty(renderer->GetWVP());
	}

	renderer->BeginDraw(0);
	renderer->BeginDraw(1);																	// Le decimos al renderer que comience a dibujar
	renderer->BindBuffer(bufferId, 0);
	renderer->BindTextureBuffer(txrBufferId, 1);											// Unimos el buffer con el buffer binding point
	renderer->DrawBuffer(vtxCount, type);													// El renderer dibuja el triangulo
	renderer->EndDraw(0);
	renderer->EndDraw(1);																	// Deja de dibujar
}

void Sprite::SetTextureBufferId(unsigned int textureBufferId) {
	UVBufferID = textureBufferId;
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
	
	SetTextureVertices(textureVertex, 4);
}