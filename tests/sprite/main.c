#include "../../Sprite.h"

#include "../LAssert/LAssert.h"




TEST_SECTION(SpriteList){
    static ListSprite * ls = NULL; // static to be initialized only once
    
    TEST_CASE(creation){
	ls = initListSprite(5);

	REQUIRE_NOT_NULL(ls);
	REQUIRE(ls->first == NULL);
	REQUIRE(ls->next == NULL);
	REQUIRE(ls->prev == NULL);
	REQUIRE(ls->current == NULL);
	REQUIRE(ls->code == 5);
	REQUIRE(ls->size == 0);
	REQUIRE(ls->side == 0);
	REQUIRE(ls->wasChanged == 0);
    }

    // not to do other test cases if font failed to be initialized
    REQUIRE_NOT_NULL(ls);

    TEST_CASE(add){
	int a1[] = {0, 1, 2, 3};
	REQUIRE(!addSprite(ls, a1[0], a1[1], a1[2], a1[3], 4, 0));
	Sprite * s1 = ls->first;
	REQUIRE_NOT_NULL(s1);
	for(int i = 0; i < 4; ++i){
	    REQUIRE(s1->coords[i] == a1[i], "%d\n", i);
	}
	REQUIRE(s1->lifespan == 4);
	REQUIRE(s1->code == 0);
	REQUIRE(s1->next == s1);
	REQUIRE(s1->prev == s1);
	REQUIRE(ls->size == 1);
	REQUIRE(ls->current == s1);
	
	int a2[] = {3, 2, 1, 0};
	REQUIRE(!addSprite(ls, a2[0], a2[1], a2[2], a2[3], 0, 4));
	Sprite * s2 = ls->first->next;
	REQUIRE_NOT_NULL(s2);
	for(int i = 0; i < 4; ++i){
	    REQUIRE(s2->coords[i] == a2[i], "%d\n", i);
	}
	REQUIRE(s2->lifespan == 0);
	REQUIRE(s2->code == 4);
	REQUIRE(s2->next == s1);
	REQUIRE(s2->prev == s1);
	REQUIRE(s1->next == s2);
	REQUIRE(s1->prev == s2);
	REQUIRE(ls->size == 2);
    }

    TEST_CASE(del){
	REQUIRE_NOT_NULL(ls->first);
	REQUIRE_NOT_NULL(ls->first->next);
	Sprite * s = ls->first->next;

	REQUIRE(!delSprite(ls, 0));
	REQUIRE(ls->size == 1);
	REQUIRE(ls->first == s);
	REQUIRE(s->prev == s);
	REQUIRE(s->next == s);
	REQUIRE(ls->current == s);
	REQUIRE(delSprite(ls, 0));

	REQUIRE(!delSprite(ls, 4));
	REQUIRE(ls->size == 0);
	REQUIRE(ls->first == NULL);
	REQUIRE(delSprite(ls, 4));
    }

    TEST_CASE(set){
	REQUIRE(!addSprite(ls, 0, 1, 2, 3, 4, 0));
	REQUIRE(!addSprite(ls, 3, 2, 1, 0, 0, 4));
	REQUIRE_NOT_NULL(ls->current);
	REQUIRE(ls->current->code == 0);
	
	REQUIRE(!setSprite(ls, 4));
	REQUIRE_NOT_NULL(ls->current);
	REQUIRE(ls->current->code == 4);
	REQUIRE(setSprite(ls, 3));

	REQUIRE(!setLifeSpanSprite(ls, 4, 42));
	REQUIRE(ls->current->lifespan == 42);
	REQUIRE(setLifeSpanSprite(ls, 3, 21));
    }

    if(ls){
	freeListSprite(ls);
	ls = NULL;
    }
}




TEST_SECTION(AnimationList){
    static ListAnimation * la = NULL; // static to be initialized only once
    
    TEST_CASE(creation){
	la = initListAnimation();

	REQUIRE_NOT_NULL(la);
	REQUIRE(la->size == 0);
	REQUIRE(la->first == NULL);
	REQUIRE(la->current == NULL);
    }

    // not to do other test cases if font failed to be initialized
    REQUIRE_NOT_NULL(la);
    
    TEST_CASE(addAnimation){
    }
    
    TEST_CASE(delAnimation){
    }
    
    TEST_CASE(addSprite){
    }
    
    TEST_CASE(delSprite){
    }
    
    TEST_CASE(set){
    }

    freeListAnimation(la);
}
