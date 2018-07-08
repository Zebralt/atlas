#include "global.hpp"
#include "layout.hpp"
#include "panel.hpp"

void ColumnLayout::layoutTarget() {
    uint tmp_size = target->size();
    for (uint i=0;i<tmp_size; i++) {
        Widget* w = target->get(i);//(*target)[i];
        if (w) {
            if (margin) {
                float true_global_height = target->getSize().h - margin * (tmp_size + 1);
                float true_element_height = true_global_height/tmp_size;
                float remainder = true_element_height - (long) true_element_height;
//                LOG("remainder=" << remainder);
                if (remainder) {
                    /// resize time !
                    true_element_height += (1 - remainder);
                    float new_width = target->getSize().w;
                    float new_height = true_element_height*tmp_size+margin*(1+tmp_size);
                    LOG(target->getSize().h << "->" << new_height);
                    target->Widget::setSize(new_width, new_height);
                }
            }
            {
                w->setSize(target->getSize().w - margin*2, target->getSize().h/tmp_size);
                w->setPosition(sf::Vector2f(0,w->getSize().h*i));
//                w->setBackgroundColor(sf::Color(10*i+50,20*i,15*i));
            }
        }
    }
}

void RowLayout::layoutTarget() {
	uint tmp_size = target->size();
    for (uint i=0;i<tmp_size; i++) {
        Widget* w = target->get(i);//(*target)[i];
        if (w) {
            if (margin) {
                float true_global_width = target->getSize().w - margin * (tmp_size + 1);
                float true_element_width = true_global_width/tmp_size;
                float remainder = true_element_width - (long) true_element_width;
//                LOG("remainder=" << remainder);
                if (remainder) {
                    /// resize time !
                    true_element_width += (1 - remainder);
                    float new_height = target->getSize().h;
                    float new_width = true_element_width*tmp_size+margin*(1+tmp_size);
                    LOG(target->getSize().w << "->" << new_width);
                    target->Widget::setSize(new_width, new_height);
                }
            }
            {
                w->setSize(target->getSize().w/tmp_size, target->getSize().h - margin*2);
                w->setPosition(sf::Vector2f(w->getSize().w*i, 0));
//                w->setBackgroundColor(sf::Color(10*i+50,20*i,15*i));
            }
        }
    }
}

//elem:size = w - margin - margin, 	(h - margin*(elems + 1))/elems
//elem:pos  = margin,			margin + i*elems:size:h + margin*(i-1)	

void GridLayout::layoutTarget() {
    uint row_it = 0;
    uint col_it = 0;
    uint tmp_size = target->size();
    for (uint i=0;i<tmp_size;i++) {
        Widget* w =target->get(i);
        if (w) {
            /*if (margin) {
                float true_global_height = target->getSize().h - margin * (tmp_size + 1);
                float true_element_height = true_global_height/tmp_size;
                float remainder = true_element_height - (long) true_element_height;
                LOG("remainder=" << remainder);
                if (remainder) {
                    /// resize time !
                    true_element_height += (1 - remainder);
                    float new_width = target->getSize().w;
                    float new_height = true_element_height*tmp_size+margin*(1+tmp_size);
                    LOG(target->getSize().h << "->" << new_height);
                    target->Widget::setSize(new_width, new_height);
                }
            }*/
            {
                w->setSize(target->getSize().w/cols-margin*(2+cols), target->getSize().h/rows-margin*(2+rows));
                w->setPosition(sf::Vector2f(margin+w->getSize().w*col_it+col_it*margin,margin+w->getSize().h*row_it+row_it*margin));
                //w->setBackgroundColor(sf::Color(10*i+50,20*i,15*i));
            }
        }
        
        // special iterators
        if (orientation) {
            col_it++;
            if (col_it >= cols) {
                col_it = 0;
                row_it++;
                if (row_it >= rows) {
                    break;
                }
            }
        }
        else {
            row_it++;
            if (row_it >= cols) {
                row_it = 0;
                col_it++;
                if (col_it >= rows) {
                    break;
                }
            }
        }
        
    }
}