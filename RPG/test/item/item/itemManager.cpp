//-----------------------------------------------------------------------------------------
#include "itemManager.h" 
//-----------------------------------------------------------------------------------------
ItemManager::ItemManager()
:
m_ikAuxItem(NULL)
{
    /***/
}
//-----------------------------------------------------------------------
ItemManager::~ItemManager(){
    delete m_ikAuxItem;
    m_ikAuxItem = NULL;
    /***/
}
//-----------------------------------------------------------------------
Item* ItemManager::CreateItem(int m_iType){

	switch(m_iType){
		case TYPE_ARMOR:{
		//	m_ikAuxItem = new Armor();
			m_lkItemList.push_back(m_ikAuxItem);
			break;
						}
		case TYPE_WEAPON:{
		//	m_ikAuxItem = new Weapon();
			m_lkItemList.push_back(m_ikAuxItem);
			break;
		}
	}
	return m_ikAuxItem;
}
void ItemManager::DeleteItem(Item *kItem){

    // Si el item no es nulo
    if (kItem){

        // Enviamos el iterador al principio
        m_lkItemListIterator = m_lkItemList.begin();

        // Mientras el iterador no llegue al final
        // y el valor sea diferente al Item
        while ((m_lkItemListIterator != m_lkItemList.end()) &&
            ((*m_lkItemListIterator != kItem))){
            // Incrementamos el iterador
            m_lkItemListIterator++;
        }

        // Si el iterador llego al final, salimos del metodo
        if (m_lkItemListIterator == m_lkItemList.end()){
            return;
        }
        // Si el valor de iterador es el item
        if ((*m_lkItemListIterator) == kItem){

            // Quitamos el item de la lista.
            m_lkItemList.remove(kItem);
            delete kItem;
            kItem = NULL;
        }
  }
}