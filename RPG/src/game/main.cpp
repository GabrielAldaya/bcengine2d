
//--------------------------------------------------------------------------------
#include <Windows.h>
#include "RPG.h"
//--------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int intnShowCmd)
{
	BasicGame* pkGame = new BasicGame(hInstance);

	if(!pkGame->StartUp())
		return 0;

	// flag para cortar el main loop
	bool bQuit = false;
	MSG kMsg;

	while(!pkGame->Loop() && !bQuit)
	{
		// capturo el mensaje de Windows
		if (PeekMessage(&kMsg,NULL,0,0,PM_REMOVE))
		{
			switch(kMsg.message)
			{
				// si es un mensaje de salir de la aplicacion
				case WM_QUIT:
					bQuit = true;
					break;

				// si es un mensaje de presionar una tecla
				case WM_KEYDOWN:
				{
					int iKeyCode = (int)kMsg.wParam;

					switch (iKeyCode)
					{
						// si esa tecla es ESC
						case VK_ESCAPE:
   							bQuit = true;
							break;
					}
					break;
				}
			}

			// le paso el mensaje de vuelta a Windows
			TranslateMessage(&kMsg);
			DispatchMessage(&kMsg);
		}
	}

	// termino el juego
	pkGame->ShutDown();


	return 0;
}
//--------------------------------------------------------------------------------
/*int main () {
	Component cmp1;
	Component cmp2;
	Item		item;
//	Actor       npc;
//	Quest       quest;
	cmp1.onAddedListener(ChildAddedEvent::CHILD_ADDED_EVENT, &item);
	cmp1.onAddedListener(ChildRemoveEvent::CHILD_REMOVE_EVENT, &item);

//	cmp1.onAddedListener(DieActorEvent::DIE_ACTOR_EVENT, &quest);
	//npc.onAddedListener(DieActorEvent::DIE_ACTOR_EVENT, &npc);
	
	
	cmp1.addNewChild(&cmp2);
	cmp1.removeChild(&cmp2);

	//npc.onEvent(DieActorEvent::DIE_ACTOR_EVENT, &npc);
}*/
